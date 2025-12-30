#include "OpenGlLayer.h"

#include "GL/glew.h"

namespace cedar
{
	OpenGlLayer::OpenGlLayer()
	{
	}

	OpenGlLayer::~OpenGlLayer()
	{
		glDeleteProgram(shaderProgram);
	}

	void OpenGlLayer::OnAttach()
	{
		float vertices[] = {
			// first triangle
			-0.9f, -0.5f, 0.0f, // left
			-0.0f, -0.5f, 0.0f, // right
			-0.45f, 0.5f, 0.0f, // top
			// second triangle
			0.0f, -0.5f, 0.0f, // left
			0.9f, -0.5f, 0.0f, // right
			0.45f, 0.5f, 0.0f  // top
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//vertex shader
		vertexSquareSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;

			void main()
			{
				gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
			}	

		)";

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vertexSource = vertexSquareSrc.c_str();
		glShaderSource(vertexShader, 1, &vertexSource, nullptr);
		glCompileShader(vertexShader);

		int success {};
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			CEDAR_ERROR("SHADER::VERTEX::COMPILATION_FAILED:   {}", infoLog);
		}

		//fragment shader
		fragmentSquareSrc = R"(
			#version 330 core
            
            layout(location = 0) out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
            }
		)";

		fragmentShader               = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentSource = fragmentSquareSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			CEDAR_ERROR("SHADER::FRAGMENT::COMPILATION_FAILED:   {}", infoLog);
		}

		//shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			CEDAR_ERROR("SHADER::LINKING_FAILED:   {}", infoLog);
		}

		//Delete shaders after successful linking
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(shaderProgram);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void OpenGlLayer::OnDetach()
	{
	}

	void OpenGlLayer::OnEvent(IEvent& event)
	{
	}

	void OpenGlLayer::OnRender(float alpha)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void OpenGlLayer::OnImGuiRender()
	{
	}
} // namespace cedar
