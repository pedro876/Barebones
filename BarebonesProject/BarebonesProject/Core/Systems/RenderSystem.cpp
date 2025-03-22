#include "RenderSystem.h"

namespace Barebones
{

	Signature RenderSystem::CreateSignature()
	{
		Signature s;
		s.set(Coordinator::GetComponentType<Transform>());
		s.set(Coordinator::GetComponentType<MeshRenderer>());
		return s;
	}

	void RenderSystem::Init()
	{

	}

	void RenderSystem::Update(float dt)
	{
		GL::SetupCameraProperties(CameraSystem::mainViewProj);
		for (auto& entity : mEntities)
		{
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			auto& meshRenderer = Coordinator::GetComponent<MeshRenderer>(entity);
			GL::DrawMeshRenderer(transform, meshRenderer);
		}
	}

	void RenderSystem::EntityDestroyed(Entity entity)
	{

	}
}