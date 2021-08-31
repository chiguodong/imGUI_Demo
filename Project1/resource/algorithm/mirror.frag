varying vec2 vTexcoord;

uniform sampler2D diffuseMap;

void main()
{
    gl_FragColor = vec4(texture2D(diffuseMap, vTexcoord).rgb,1.0);
}
