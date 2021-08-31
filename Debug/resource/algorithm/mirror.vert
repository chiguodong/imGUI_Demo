attribute vec3 position;
attribute vec2 texcoord;

varying vec2 vTexcoord;

void main(){
    vTexcoord = texcoord;
    vTexcoord.x = 1.0 - vTexcoord.x;
    gl_Position = vec4(position,1.0);
}
