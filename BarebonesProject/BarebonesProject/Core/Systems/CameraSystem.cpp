#include "CameraSystem.h"

namespace Barebones
{
	Signature CameraSystem::CreateSignature()
	{
		Signature s;
		s.set(Coordinator::GetComponentType<Transform>());
		s.set(Coordinator::GetComponentType<Camera>());
		return s;
	}

	void CameraSystem::Update(float dt)
	{
		unsigned int maxPriority = 0;
		Camera* mainCameraPtr = nullptr;
		Transform* mainTransformPtr = nullptr;
		for (auto& entity : mEntities)
		{
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			auto& camera = Coordinator::GetComponent<Camera>(entity);
			if (camera.priority >= maxPriority)
			{
				mainCamera = entity;
				mainCameraPtr = &camera;
				mainTransformPtr = &transform;
				maxPriority = camera.priority;
			}
		}

		if (mainCameraPtr)
		{
			glm::mat4 viewMat = mainTransformPtr->GetLocalToWorldMatrix();
			viewMat = glm::inverse(viewMat);
			//glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 9.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			//glm::mat4 viewMat = glm::mat4{ 1.0f };
			//viewMat = glm::toMat4(glm::quat(glm::vec3(0.0f, glm::radians(180.0f), 0.0f))) * viewMat;
			//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, 5.0f));
			//viewMat = glm::inverse(viewMat);
			glm::mat4 projMat = mainCameraPtr->GetProjectionMatrix(GL::GetAspectRatio());
			mainViewProj = projMat * viewMat;
		}
	}

	void CameraSystem::EntityDestroyed(Entity entity)
	{
		
	}
}