attribute vec3 position;
attribute vec3 normal;
attribute vec2 texcoord;
attribute vec3 tangent;

uniform mat4 worldMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

uniform float cameraFar;
uniform float cameraNear;

varying vec2 vTexcoord;
varying vec3 vNormal;
varying vec3 vWorldPosition;
varying vec3 vTangent;

float LinearizeDepth(float depth)
{
    float near = cameraNear;
    float far = cameraFar;
    float z = depth * 2.0 - 1.0; // back to NDC
    float dep = (2.0 * near * far) / (far + near - z * (far - near));
    return ((dep - near) / (far - near));
}

void main(){
    vTexcoord = texcoord;
    vTangent = mat3(worldMat) * tangent;
    vWorldPosition = vec3(worldMat * vec4(position, 1.0));     //transform to then     worldMat
    vNormal = mat3(worldMat) * normal;
    vec4 unLinerPosition = projectionMat * viewMat * worldMat * vec4(position,1.0);
    gl_Position = unLinerPosition;
}
