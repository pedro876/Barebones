//STD INCLUDES:

#include "Core/BarebonesEngine.h"

using namespace Barebones;

int main()
{
	Coordinator coordinator{};
	GL gl{};
	coordinator.Init();

	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<MeshRenderer>();
	coordinator.RegisterComponent<Camera>();

	Shader shaderProgram = Shader("Core/Shaders/vertex.vert", "Core/Shaders/fragment.frag");
	Material material = Material("M_Test", &shaderProgram);

	Mesh quad = Mesh(Primitive::Quad);

	std::shared_ptr<RenderSystem> renderSystem = coordinator.RegisterSystem<RenderSystem>();
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<MeshRenderer>());
	coordinator.SetSystemSignature<RenderSystem>(signature);

	std::shared_ptr<CameraSystem> cameraSystem = coordinator.RegisterSystem<CameraSystem>();
	Signature signature2;
	signature2.set(coordinator.GetComponentType<Transform>());
	signature2.set(coordinator.GetComponentType<Camera>());
	coordinator.SetSystemSignature<CameraSystem>(signature2);
	

	Entity entity = coordinator.CreateEntity();

	coordinator.AddComponent(entity, Transform{});
	coordinator.AddComponent(entity, MeshRenderer{});

	Entity camera = coordinator.CreateEntity();
	coordinator.AddComponent(camera, Camera{});
	coordinator.AddComponent(camera, Transform{});

	MeshRenderer& meshRenderer = coordinator.GetComponent<MeshRenderer>(entity);
	meshRenderer.mesh = &quad;
	meshRenderer.material = &material;

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();

		cameraSystem->Update(coordinator, 1.0f);
		renderSystem->Update(coordinator, gl, 1.0f);

		gl.EndFrame();
	}

	return 0;
}