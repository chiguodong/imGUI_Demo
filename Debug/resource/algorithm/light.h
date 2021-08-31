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
