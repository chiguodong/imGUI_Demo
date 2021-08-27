struct Light {
    vec3 direction;
    vec3 intensity;
    float attenuation;
};

varying vec2 vTexcoord;
varying vec3 vNormal;
varying vec3 vWorldPosition;
varying vec3 vTangent;

uniform samplerCube envMap;
uniform samplerCube prefilterMap;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D mraMap;

uniform sampler2D brdfLUT;

uniform vec3 cameraPosition;

uniform float fresnelF0;

#define MEDIUMP_FLT_MAX    65504.0
#define saturateMediump(x) min(x, MEDIUMP_FLT_MAX)
const float PI = 3.14159265359;

struct DirLight {
    vec3 position;
    vec3 direction;
    vec3 intensity;
};

struct PointLight {
    vec3 position;
    vec3 intensity;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 intensity;
    float cutOff;
    float outerCutOff;
};

#define NR_DIR_LIGHTS   1
#define NR_POINT_LIGHTS 0
#define NR_SPOT_LIGHTS  0

uniform DirLight dirLights[NR_DIR_LIGHTS];
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//uniform SpotLight spotLights[NR_SPOT_LIGHTS];

//struct light was definated in main BRDF
Light parseDirLight(vec3 worldPosition, DirLight dirLight) {
    Light ans;
    ans.direction = dirLight.direction;
    ans.intensity = dirLight.intensity;
    float attenuation;
    //vWorldPosition comes from main brdf
    float distance = length(dirLight.position - worldPosition);
    attenuation = 1.0 / (1.0/*constant*/ + 0.09/*linear*/ * distance + 0.032/*quadratic*/ * (distance * distance));
    ans.attenuation = attenuation;
    return ans;
}

Light parsePointLight(vec3 worldPosition, PointLight pointLight) {
    Light ans;
    ans.direction = normalize(pointLight.position - worldPosition);
    ans.intensity = pointLight.intensity;
    float attenuation;
    
    float distance = length(pointLight.position - worldPosition);
    attenuation = 1.0 / (1.0/*constant*/ + 0.09/*linear*/ * distance + 0.032/*quadratic*/ * (distance * distance));
    ans.attenuation = attenuation;
    return ans;
}

Light parseSpotLight(vec3 worldPosition, SpotLight spotLight) {
    Light ans;
    ans.direction = spotLight.direction;

    vec3 lightDir = normalize(spotLight.position - worldPosition);
    float theta     = dot(lightDir, normalize(-spotLight.direction));
    float epsilon   = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    ans.intensity = intensity * spotLight.intensity;

    float attenuation;

    float distance = length(spotLight.position - vWorldPosition);
    attenuation = 1.0 / (1.0/*constant*/ + 0.09/*linear*/ * distance + 0.032/*quadratic*/ * (distance * distance));
    ans.attenuation = attenuation;
    return ans;
}

Light lights[NR_DIR_LIGHTS + NR_POINT_LIGHTS + NR_SPOT_LIGHTS];

void getLights(vec3 worldPosition) {
    int tmpNum = 0;
    for (int i = 0; i < NR_DIR_LIGHTS; i++) {
        lights[tmpNum] = parseDirLight(worldPosition, dirLights[i]);
        tmpNum++;
    }
//    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
//        lights[tmpNum] = parsePointLight(worldPosition, pointLights[i]);
//        tmpNum++;
//    }
//    if (NR_SPOT_LIGHTS > 0) {
//        for (int i = 0; i < NR_SPOT_LIGHTS; i++) {
//            lights[tmpNum] = parseSpotLight(worldPosition, spotLights[i]);
//            tmpNum++;
//        }
//    }
}


vec3 getNormalFromMap(){
    vec3 tangentNormal = texture2D(normalMap, vTexcoord).rgb * 2.0 - vec3(1.0);

    vec3 N = normalize(vNormal);
    vec3 T = normalize(vTangent);
    vec3 B = -normalize(cross(N,T));
    mat3 TBN = mat3(T,B,N);
    return normalize(TBN * normalize(tangentNormal));
}

//cosTheta : n dot v
vec3 fresnelSchlick(float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

float V_SmithGGXCorrelatedFast(float NoV, float NoL, float roughness) {
    float a = roughness * roughness;
    float GGXV = NoL * (NoV * (1.0 - a) + a);
    float GGXL = NoV * (NoL * (1.0 - a) + a);
    return 0.5 / (GGXV + GGXL);
}

float D_GGX(const vec3 n, const vec3 h, float roughness) {
    vec3 NxH = cross(n, h);
    float NoH = dot(n,h);
    float a = NoH * roughness;
    float k = roughness / (dot(NxH, NxH) + a * a);
    float d = k * k * (1.0 / PI);
    return saturateMediump(d);
}

const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

vec3 getEnvColor(vec3 normal) {
    vec3 color = textureCube(envMap, normal).rgb;
    return color;
}

vec3 getSpecularColor(vec3 uv, float roughness) {
    if (roughness > 0.5) {
        return textureCube(envMap, uv).rgb;
    } else {
        return textureCube(prefilterMap, uv).rgb;
    }
}

struct BRDFParam {
    float metallic  ;
    float roughness ;
    float ao        ;
};

vec3 BRDF(Light light, BRDFParam p, vec3 N, vec3 V, vec3 albedo) {
    
    vec3 F0 = vec3(fresnelF0);
    F0 = mix(F0, albedo.rgb, p.metallic);
    
    vec3 L = -light.direction;
    vec3 H = normalize(V + L);
    float NoV = abs(dot(N, V)) + 1e-5;
    float NoL = clamp(dot(N, L), 0.0, 1.0);
//base brdf
//pre calculate of Standard brdf
    vec3 radiance = light.attenuation * light.intensity;
    vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
#ifdef ANISOTROPIC
    float NDFG = getAnitropicMicroNormal(N, L, H, V, p.roughness);
    vec3 specular = NDFG * F;
#else
    float NDF = D_GGX(N, H, p.roughness);
    float G   = V_SmithGGXCorrelatedFast(NoV, NoL, p.roughness);
    vec3 nominator = NDF * G * F;
    vec3 specular = nominator;
#endif
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - p.metallic;
    float NdotL = max(dot(N, L), 0.0);
#ifdef CLEARCOAT
    float VoH = clamp(dot(V, H), 0.0, 1.0);
    float Frc = getClearCoatPower(N, H,  L);
    vec3 color = ((kD * Diffuse_Burley_Disney(albedo.rgb, p.roughness, NoV, NoL, VoH) + specular * (1.0 - Frc))* (1.0 - Frc) + Frc) * radiance;
#else
    vec3 color = (kD * albedo.rgb / PI + specular) * radiance * NdotL;
#endif
    //color = vec3(-specular);
    return color;
}

void main()
{
    vec3 albedo = pow(texture2D(diffuseMap, vTexcoord).rgb, vec3(2.2));
    getLights(vWorldPosition);
    BRDFParam p;
    vec3 mraColor   = texture2D(mraMap,vTexcoord).rgb;
    p.metallic  = 0.0;
    p.roughness = mraColor.g;
    p.ao        = mraColor.b;
    vec3 N = vNormal;
    vec3 V = normalize(cameraPosition - vWorldPosition);
    vec3 R = reflect(-V, N);
    
    vec3 Lo = vec3(0.0);
//base brdf
//pre calculate of Standard brdf
    Lo += BRDF(lights[0], p, N, V, albedo);
    
#ifdef SUBSURFACE
    Lo += getSubsurfaceColor(V, -lights[0].direction, N, albedo);
#endif
    
    vec3 color = Lo;//ambient + Lo;
    color = pow(color, vec3(1.0 / 2.2));
    
    gl_FragColor = vec4(color  , 1.0);
}
