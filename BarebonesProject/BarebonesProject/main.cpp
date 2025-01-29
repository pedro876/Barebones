//STD INCLUDES:

#include "Coordinator.h"
#include "RenderSystem.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Transform.h"

using namespace Barebones;

int main()
{
	Coordinator coordinator{};
	GL gl{};
	coordinator.Init();

	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<MeshRenderer>();

	Shader shaderProgram = Shader("vertex.vert", "fragment.frag");
	Material material = Material("M_Test", &shaderProgram);

	Mesh quad = Mesh(Primitive::Quad);

	std::shared_ptr<RenderSystem> renderSystem = coordinator.RegisterSystem<RenderSystem>();
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<MeshRenderer>());

	Entity entity = coordinator.CreateEntity();

	coordinator.AddComponent(entity, Transform{});
	coordinator.AddComponent(entity, MeshRenderer{});

	MeshRenderer& meshRenderer = coordinator.GetComponent<MeshRenderer>(entity);
	meshRenderer.mesh = &quad;
	meshRenderer.material = &material;

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();

		renderSystem->Update(coordinator, gl, 1.0f);

		gl.EndFrame();
	}

	return 0;
}