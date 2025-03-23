#pragma once

#include "GL/GL.h"
#include "DB/DB.h"
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Systems/CameraSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/TransformSystem.h"
#include "Systems/LightingSystem.h"
#include "Systems/InputSystem.h"
#include "DB/Model/Model.h"

namespace Barebones
{
    void StartEngine();
    void StopEngine();
}