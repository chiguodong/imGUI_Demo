uniform float wrapped;
vec3 wrappedDiffuse(float diffuse) {
    diffuse = (diffuse + wrapped) / (1.0 + wrapped);
    return diffuse;
}
