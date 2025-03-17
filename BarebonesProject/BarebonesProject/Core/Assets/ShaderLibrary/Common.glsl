uniform mat4 _Model;

layout (std140) uniform Matrices
{
    mat4 _ViewProj;
};

#define saturate(x) clamp(x, 0.0, 1.0)
#define pow2(x) (x*x)