//STD INCLUDES:

#include "GL.h"
#include "GameObject.h"
#include "Shader.h"

int main()
{
	GL gl{};

	GameObject testObject{ "testObject" };
	MeshRenderer* meshRenderer = testObject.AddComponent<MeshRenderer>();

	Mesh* quad = new Mesh(Primitive::Quad);
	meshRenderer->mesh = quad;

	Shader shaderProgram = Shader("vertex.vert", "fragment.frag");

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();

		shaderProgram.use();
		gl.DrawMeshRenderer(*meshRenderer);

		gl.EndFrame();
	}

	return 0;
}