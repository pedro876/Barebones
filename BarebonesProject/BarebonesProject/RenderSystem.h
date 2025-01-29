#pragma once

#include "Coordinator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "GL.h"

namespace Barebones
{
	class RenderSystem : public System
	{
	public:
		
		void Init();
		void Update(Coordinator& coordinator, GL& gl, float dt);
	};
}

