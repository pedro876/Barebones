#pragma once
#include "../ECS/Coordinator.h"
#include "../ECS/SystemManager.h"
#include "../GL/Input.h"

namespace Barebones
{

	class InputSystem : public System
	{
	public:
		InputSystem();
		Signature CreateSignature() override;
		void EntityDestroyed(Entity entity) override;
		void Update(float dt);
		void EndFrame();
		static Input* GetInput(Key key);
		static Input* GetInput(MouseButton mouseButton);
		static glm::vec2 GetMouseAxis();

	private:
		static inline unsigned int inputCount = 0;
		static inline Input inputs[100];
		static inline double lastMouseX;
		static inline double lastMouseY;
		static inline bool everDetectedMouse;
		static inline glm::vec2 mouseAxis;
		static inline const float sensitivity = 0.1f;
		static inline Input* input_escape = InputSystem::GetInput(Key::Escape);
		static inline Input* input_leftClick = InputSystem::GetInput(MouseButton::LeftClick);
		static inline bool changedCursorInputMode = false;
		

		static void OnMouse(GLFWwindow* window, double xpos, double ypos);
	};
}