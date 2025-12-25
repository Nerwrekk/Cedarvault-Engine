#include "Renderer/Camera2D.h"

namespace cedar
{
	Camera2D::Camera2D(int width, int height)
	    : m_screenWidth(width), m_screenHeight(height), m_scale(1.f),
	      m_position { glm::vec2 { 0 } }, m_cameraMatrix { 1.f }, m_needsMatrixUpdate(true)
	{
		m_orthoMatrix = glm::ortho(
		    0.f,                  //left
		    (float)m_screenWidth, //right
		    0.f,                  //bottom
		    (float)m_screenHeight //top
		);
	}

	void Camera2D::Update()
	{
		if (!m_needsMatrixUpdate)
		{
			return;
		}

		m_orthoMatrix = glm::ortho(
		    0.f,                  //left
		    (float)m_screenWidth, //right
		    0.f,                  //bottom
		    (float)m_screenHeight //top
		);

		//Translate
		glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.f);
		m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

		//Scale
		glm::vec3 scale(m_scale, m_scale, 0.f);
		m_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * m_cameraMatrix;

		m_needsMatrixUpdate = false;
	}

	void Camera2D::SetPosition(const glm::vec2& newPosition)
	{
		m_position          = newPosition;
		m_needsMatrixUpdate = true;
	}

	void Camera2D::SetScale(float newScale)
	{
		m_scale             = newScale;
		m_needsMatrixUpdate = true;
	}

	void Camera2D::Resize(int width, int height)
	{
		m_screenWidth  = width;
		m_screenHeight = height;

		m_needsMatrixUpdate = true;
	}

	glm::vec2 Camera2D::GetPosition()
	{
		return m_position;
	}

	float Camera2D::GetScale()
	{
		return m_scale;
	}

	inline glm::mat4 Camera2D::GetCameraMatrix()
	{
		return m_cameraMatrix;
	}
}

// namespace cedar
