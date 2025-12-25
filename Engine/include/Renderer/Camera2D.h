#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cedar
{
	class Camera2D
	{
	public:
		Camera2D(int width, int height);
		~Camera2D();

		void Update();

		void SetPosition(const glm::vec2& newPosition);
		void SetScale(float newScale);
		void Resize(int width, int height);

		glm::vec2 GetPosition();
		float GetScale();
		inline glm::mat4 GetCameraMatrix();

	private:
		int m_screenWidth;
		int m_screenHeight;
		float m_scale;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
		bool m_needsMatrixUpdate;
	};

} // namespace cedar
