#include "CameraSystem.h"

namespace Barebones
{
	Entity CameraSystem::mainCamera{};
	glm::mat4 CameraSystem::mainViewProj{ glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f) };

	void CameraSystem::Update(Coordinator& coordinator, float dt)
	{
		unsigned int maxPriority = 0;
		Camera* mainCameraPtr = nullptr;
		Transform* mainTransformPtr = nullptr;
		for (auto& entity : mEntities)
		{
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& camera = coordinator.GetComponent<Camera>(entity);
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
			glm::mat4 projMat = mainCameraPtr->GetProjectionMatrix(16.0f / 9.0f);
			mainViewProj = projMat * viewMat;
		}
	}
}