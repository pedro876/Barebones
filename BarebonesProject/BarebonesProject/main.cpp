//STD INCLUDES:

#include "GL.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

int main()
{
	GL gl{};

	GameObject wizard{ "wizard" };
	std::cout << wizard << std::endl;

	Mesh quad{ Primitive::Quad };
	Shader shaderProgram = Shader("vertex.vert", "fragment.frag");

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();

		shaderProgram.use();
		gl.DrawMesh(quad);

		gl.EndFrame();
	}

	return 0;
}