attribute vec3 position;

uniform mat4 worldMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main(){
    gl_Position = projectionMat * viewMat * worldMat * vec4(position,1.0);;
}
