//STD INCLUDES:

#include "Core/BarebonesEngine.h"

using namespace Barebones;

Entity CreateCube(Mesh* cubeMesh, Material* material)
{
	Entity entity = Coordinator::CreateEntity();

	Coordinator::AddComponent(entity, Transform{});
	Coordinator::AddComponent(entity, MeshRenderer{});

	MeshRenderer& meshRenderer = Coordinator::GetComponent<MeshRenderer>(entity);
	meshRenderer.mesh = cubeMesh;
	meshRenderer.material = material;
	return entity;
}

int main()
{
	GL gl{};

	Coordinator::RegisterComponent<Transform>();
	Coordinator::RegisterComponent<MeshRenderer>();
	Coordinator::RegisterComponent<Camera>();

	std::shared_ptr<RenderSystem> renderSystem = Coordinator::RegisterSystem<RenderSystem>();
	Signature signature;
	signature.set(Coordinator::GetComponentType<Transform>());
	signature.set(Coordinator::GetComponentType<MeshRenderer>());
	Coordinator::SetSystemSignature<RenderSystem>(signature);

	std::shared_ptr<CameraSystem> cameraSystem = Coordinator::RegisterSystem<CameraSystem>();
	Signature signature2;
	signature2.set(Coordinator::GetComponentType<Transform>());
	signature2.set(Coordinator::GetComponentType<Camera>());
	Coordinator::SetSystemSignature<CameraSystem>(signature2);

	std::shared_ptr<TransformSystem> transformSystem = Coordinator::RegisterSystem<TransformSystem>();
	Signature signature3;
	signature3.set(Coordinator::GetComponentType<Transform>());
	Coordinator::SetSystemSignature<TransformSystem>(signature3);


	//Shader shaderProgram = Shader("Default Shader", "Core/Shaders/vertex.vert", "Core/Shaders/fragment.frag");
	//auto shaderProgram = DB<Shader>::Register(std::make_shared<Shader>("Default Shader", "Core/Assets/Shaders/vertex.vert", "Core/Assets/Shaders/fragment.frag"));
	auto shaderProgram = DB<Shader>::Register(std::make_shared<Shader>("Default Shader", "Core/Assets/Shaders/DefaultShader.glsl"));
	//auto material = DB<Material>::Register(std::make_shared<Material>("M_Test", shaderProgram));
/*	auto model = DB<Model>::Register(std::make_shared<Model>("Core/Assets/Models/Cube.fbx")).lock();
	model->LoadModel();
	Mesh* cube = model->GetMesh(0)*/;

	auto testRoom = DB<Model>::Register(std::make_shared<Model>("Game/Assets/Models/TestRoom.fbx")).lock();
	testRoom->LoadModel();

	for (int i = 0; i < testRoom->GetMeshCount(); i++)
	{
		std::cout << testRoom->GetMesh(i)->GetName() << std::endl;
	}

	Entity cameraEntity = Coordinator::CreateEntity();
	Camera& camera = Coordinator::AddComponent(cameraEntity, Camera{});
	Coordinator::AddComponent(cameraEntity, Transform{});

	Transform& cameraTransform = Coordinator::GetComponent<Transform>(cameraEntity);
	cameraTransform.SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	cameraTransform.SetLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));

	//Coordinator::DestroyEntity(1);

	/*Entity eCube1 = CreateCube(cube, material);
	Entity eCube2 = CreateCube(cube, material);

	Transform& tCube1 = Coordinator::GetComponent<Transform>(eCube1);
	Transform& tCube2 = Coordinator::GetComponent<Transform>(eCube2);
	tCube2.SetLocalPosition(glm::vec3(1.5f, 1.5f, 0.0f));
	tCube2.SetLocalScale(glm::vec3(0.5f));rx
	TransformSystem::AddChild(eCube1, eCube2);*/

	double time = glfwGetTime();
	float deltaTime = 0.0f;

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();
		
		//Update cubes
		/*glm::quat cube1Rot = tCube1.GetLocalRotation();
		cube1Rot *= glm::quat(glm::radians(glm::vec3(30.0f * deltaTime, 0.0f, 0.0f)));
		tCube1.SetLocalRotation(cube1Rot);
		glm::quat cube2Rot = tCube2.GetLocalRotation();
		cube2Rot *= glm::quat(glm::radians(glm::vec3(0.0f, 20.0f * deltaTime, 0.0f)));
		tCube2.SetLocalRotation(cube2Rot);*/

		//Update camera
		glm::vec3 localPos = cameraTransform.GetLocalPosition();
		localPos = glm::rotate(glm::quat(glm::radians(glm::vec3(0.0f, 30.0f * deltaTime, 0.0f))), localPos);
		glm::quat localRot = glm::quatLookAt(-glm::normalize(localPos), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraTransform.SetLocalPosition(localPos);
		cameraTransform.SetLocalRotation(localRot);
		glm::vec3 eulerAngles = glm::eulerAngles(localRot);
		eulerAngles = glm::degrees(eulerAngles);

		//Update systems
		transformSystem->Update();
		cameraSystem->Update(deltaTime);
		renderSystem->Update(gl, deltaTime);

		gl.EndFrame();

		double newTime = glfwGetTime();
		deltaTime = newTime - time;
		time = newTime;

		//glm::vec3 tCube2pos = TransformSystem::GetWorldPosition(tCube2);
		//std::cout << tCube2pos.x << " " << tCube2pos.y << " " << tCube2pos.z << std::endl;
	}

	return 0;
}