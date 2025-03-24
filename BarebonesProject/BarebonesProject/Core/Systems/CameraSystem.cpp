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

	void CameraSystem::EntityDestroyed(Entity entity)
	{

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
			UpdateFlyCamera(dt, mainTransformPtr, mainCameraPtr);
			glm::mat4 viewMat = TransformSystem::GetWorldTransform(*mainTransformPtr); //mainTransformPtr->GetDirtyLocalToWorldMatrix();
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

	void CameraSystem::UpdateFlyCamera(float dt, Transform* transform, Camera* camera)
	{
		const float speed = 3.0f;
		const float shiftSpeed = 9.0f;
		glm::vec3 pos = transform->GetDirtyWorldPosition();
		glm::vec3 forward = transform->GetDirtyForward();
		glm::vec3 right = transform->GetDirtyRight();
		glm::vec3 up = transform->GetDirtyUp();

		float xAxis = 0.f;
		float yAxis = 0.f;

		if (inputForward->isPressed) yAxis -= 1.f;
		if (inputBack->isPressed) yAxis += 1.f;
		if (inputRight->isPressed) xAxis += 1.f;
		if (inputLeft->isPressed) xAxis -= 1.f;

		if (xAxis != 0.0f || yAxis != 0.0f)
		{
			glm::vec3 movement = glm::normalize(glm::vec3(xAxis, 0.0f, yAxis)) * dt * (inputShift->isPressed ? shiftSpeed : speed);
			pos += forward * movement.z + right * movement.x;
			transform->SetLocalPosition(pos);
		}

		glm::vec2 mouse = InputSystem::GetMouseAxis();
		if (mouse.x != 0.0f || mouse.y != 0.0f)
		{
			float pitch = -glm::degrees(asin(forward.y));

			float degreesX = -mouse.x;
			float degreesY = -mouse.y;

			if (pitch + degreesY > 89.0f)
				degreesY = 89.0f - pitch;
			if (pitch + degreesY < -89.0f)
				degreesY = -89.0f - pitch;

			glm::quat rotation = transform->GetLocalRotation();
			rotation = glm::angleAxis(glm::radians(degreesY), right) * rotation;
			rotation = glm::angleAxis(glm::radians(degreesX), glm::vec3(0.0f, 1.0f, 0.0f)) * rotation;

			transform->SetLocalRotation(rotation);
		}


		
	}

	
}