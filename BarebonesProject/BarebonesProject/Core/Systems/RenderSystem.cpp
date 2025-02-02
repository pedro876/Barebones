#include "RenderSystem.h"

namespace Barebones
{
	void RenderSystem::Init()
	{

	}

	void RenderSystem::Update(Coordinator& coordinator, GL& gl, float dt)
	{
		for (auto& entity : mEntities)
		{
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& meshRenderer = coordinator.GetComponent<MeshRenderer>(entity);
			gl.DrawMeshRenderer(CameraSystem::mainViewProj, transform, meshRenderer);
		}
	}
}