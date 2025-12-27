#include "OpenGlLayer.h"

#include "GL/glew.h"

namespace cedar
{
	OpenGlLayer::OpenGlLayer()
	{
	}

	OpenGlLayer::~OpenGlLayer()
	{
	}

	void OpenGlLayer::OnAttach()
	{
	}

	void OpenGlLayer::OnDetach()
	{
	}

	void OpenGlLayer::OnEvent(IEvent& event)
	{
	}

	void OpenGlLayer::OnRender(float alpha)
	{
		float vertices[] = {
			//First triangle
			-0.5f, -0.5f, 0.0f, //bottom left
			0.5f, -0.5f, 0.0f,  // bottom right
			0.0f, 0.5f, 0.0f
		};

		uint32_t VBO {};
		glGenBuffers(1, &VBO);

		uint32_t VAO {};
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//vertex shader
		std::string vertexSquareSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;

			void main()
			{
				gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
			}	

		)";

		uint32_t vertexShader {};
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
		std::string fragmentSquareSrc = R"(
			#version 330 core
            
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
		)";

		uint32_t fragmentShader {};
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

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
		uint32_t shaderProgram;
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

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void OpenGlLayer::OnImGuiRender()
	{
	}
} // namespace cedar
