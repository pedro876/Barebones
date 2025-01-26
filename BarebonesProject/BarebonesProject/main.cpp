//STD INCLUDES:

#include "GL.h"
#include "GameObject.h"
#include "Material.h"
#include "ComponentPool.h"

using namespace Barebones;

int main()
{
	GL gl{};

	GameObject testObject{ "testObject" };

	Shader shaderProgram = Shader("vertex.vert", "fragment.frag");
	Material material = Material("M_Test", &shaderProgram);

	MeshRenderer* meshRenderer = testObject.AddComponent<MeshRenderer>();

	Mesh quad = Mesh(Primitive::Quad);
	meshRenderer->mesh = &quad;
	meshRenderer->material = &material;

	//testObject.RemoveComponent<MeshRenderer>();

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();


		const std::vector<MeshRenderer>& renderers = ComponentPool<MeshRenderer>::GetComponents();
		int activeCount = ComponentPool<MeshRenderer>::GetActiveCount();
		for (int i = 0; i < activeCount; i++)
		{
			gl.DrawMeshRenderer(renderers[i]);
		}

		gl.EndFrame();
	}

	return 0;
}