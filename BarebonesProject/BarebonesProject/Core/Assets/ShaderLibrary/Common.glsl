// MACROS
#define saturate(x) clamp(x, 0.0, 1.0)

// FUNCTIONS
float Square(float x) { return x * x; }
vec2 Square(vec2 x) { return x * x; }
vec3 Square(vec3 x) { return x * x; }
vec4 Square(vec4 x) { return x * x; }

// INPUTS
uniform mat4 _Model;
layout (std140) uniform Matrices
{
    mat4 _ViewProj;
};