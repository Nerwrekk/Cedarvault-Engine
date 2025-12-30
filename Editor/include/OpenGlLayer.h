#pragma once

#include "CedarVault.h"
#include "Panels/SceneHierarchy.h"
#include "Panels/AssetPanel.h"

namespace cedar
{
	class OpenGlLayer : public Layer
	{
	public:
		DECL_TYPE_NAME(OpenGlLayer);

		OpenGlLayer();
		~OpenGlLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(IEvent& event) override;

		virtual void OnRender(float alpha) override; // for interpolation
		virtual void OnImGuiRender() override;

	private:
		uint32_t VBO {};
		uint32_t VAO {};

		std::string vertexSquareSrc;
		uint32_t vertexShader {};

		std::string fragmentSquareSrc;
		uint32_t fragmentShader {};

		uint32_t shaderProgram;
	};
} // namespace cedar
