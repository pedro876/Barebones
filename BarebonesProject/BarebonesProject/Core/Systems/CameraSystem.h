#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../GL/GL.h"
#include "InputSystem.h"
#include "TransformSystem.h"

namespace Barebones
{
	class CameraSystem : public System
	{
	public:
		static inline Entity mainCamera{ 0 };
		static inline glm::mat4 mainViewProj{ glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f) };
		void Update(float dt);
		void EntityDestroyed(Entity entity) override;
		Signature CreateSignature() override;

	private:
		Input* inputForward = InputSystem::GetInput(Key::W);
		Input* inputLeft = InputSystem::GetInput(Key::A);
		Input* inputBack = InputSystem::GetInput(Key::S);
		Input* inputRight = InputSystem::GetInput(Key::D);
		Input* inputShift = InputSystem::GetInput(Key::Shift);

		void UpdateFlyCamera(float dt, Transform* transform, Camera* camera);
	};
}