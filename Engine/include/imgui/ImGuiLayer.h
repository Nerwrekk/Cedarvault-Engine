#pragma once

#include "Application/Layer.h"
#include "Common/Core.h"
#include "imgui.h"
#include "imgui/bindings/imgui_impl_opengl3.h"
#include "imgui/bindings/imgui_impl_sdlrenderer.h"
#include "imgui/bindings/imgui_impl_sdl.h"

struct ImGuiContext;

namespace cedar
{
	class ImGuiLayer : public Layer
	{
	public:
		DECL_TYPE_NAME(ImGuiLayer);

		ImGuiLayer();
		~ImGuiLayer();

		void OnBeginRender();
		void OnEndRender();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnImGuiRender() override;

		ImGuiContext* GetImGuiContext();

	private:
		float m_time {};
	};
}