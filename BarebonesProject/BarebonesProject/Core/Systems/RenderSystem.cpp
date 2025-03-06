#include "RenderSystem.h"

namespace Barebones
{
	void RenderSystem::Init()
	{

	}

	void RenderSystem::Update(GL& gl, float dt)
	{
		gl.SetupCameraProperties(CameraSystem::mainViewProj);
		for (auto& entity : mEntities)
		{
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			auto& meshRenderer = Coordinator::GetComponent<MeshRenderer>(entity);
			gl.DrawMeshRenderer(transform, meshRenderer);
		}
	}

	void RenderSystem::EntityDestroyed(Entity entity)
	{

	}
}