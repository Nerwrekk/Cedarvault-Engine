#pragma once

#include "Application/Application.h"
#include "Common/Input.h"
#include "Common/Logger.h"
#include "ECS/ECS.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/MovementSystem.h"
#include "Common/AssetManager.h"
#include "Common/Mindi/Mindi.h"
#include "Common/Event/Events/Events.h"
#include "Common/Event/EventBus.h"
#include "MeanScript/MeanScript.h"
#include "Common/SDL_Wrapper.h"
#include "Common/Core.h"
#include "Registry/TypeRegistry.h"
#include "imgui.h"
#include "imgui/bindings/imgui_impl_opengl3.h"
#include "imgui/bindings/imgui_impl_sdlrenderer.h"
#include "imgui/bindings/imgui_impl_sdl.h"
#include "imgui/ImGuiLayer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

#include <glm/glm.hpp>

namespace cedar
{
} // namespace cedar