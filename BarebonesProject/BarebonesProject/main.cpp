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

	Model model = Model("Core/Assets/Models/Cube.fbx");
	Mesh* cube = model.GetMesh(0);

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

	Entity cameraEntity = coordinator.CreateEntity();
	coordinator.AddComponent(cameraEntity, Camera{});
	coordinator.AddComponent(cameraEntity, Transform{});

	Transform& cameraTransform = coordinator.GetComponent<Transform>(cameraEntity);
	cameraTransform.SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	cameraTransform.SetLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));

	MeshRenderer& meshRenderer = coordinator.GetComponent<MeshRenderer>(entity);
	meshRenderer.mesh = cube;
	meshRenderer.material = &material;

	double time = glfwGetTime();
	float deltaTime = 0.0f;
	glm::vec3 localPos = cameraTransform.GetLocalPosition();

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();
		localPos = glm::rotate(glm::quat(glm::radians(glm::vec3(0.0f, 30.0f * deltaTime, 0.0f))), localPos);
		glm::quat localRot = glm::quatLookAt(-glm::normalize(localPos), glm::vec3(0.0f, 1.0f, 0.0f));
		
		cameraTransform.SetLocalPosition(localPos);
		cameraTransform.SetLocalRotation(localRot);
		glm::vec3 eulerAngles = glm::eulerAngles(localRot);
		eulerAngles = glm::degrees(eulerAngles);

		cameraSystem->Update(coordinator, deltaTime);
		renderSystem->Update(coordinator, gl, deltaTime);

		gl.EndFrame();

		double newTime = glfwGetTime();
		deltaTime = newTime - time;
		time = newTime;
	}

	return 0;
}