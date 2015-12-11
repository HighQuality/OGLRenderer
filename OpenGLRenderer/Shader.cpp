#include "Shader.h"
#include <vector>
#include <string>
#include <Matrix33.h>

void printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

Shader::Shader()
{
	program = glCreateProgram();

	GLuint vertexShader,
		fragmentShader;
	const GLchar* vertexShaderSource[] = { "#version 110\n"
		"attribute vec2 aPosition;\n"
		"attribute vec2 aTexCoord;\n"
		"attribute vec4 aColor;\n"
		"varying vec2 TexCoord0;\n"
		"varying vec4 Color;\n"
		"uniform mat3 uWorldToViewport;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(vec3(aPosition, 1.0) * uWorldToViewport, 1.0);\n"
		"TexCoord0 = aTexCoord;\n"
		"Color = aColor;\n"
		"}"
	};
	const GLchar* fragmentShaderSource[] = { "#version 110\n"
		"uniform sampler2D gSampler;"
		"varying vec2 TexCoord0;\n"
		"varying vec4 Color;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor = texture2D(gSampler, TexCoord0) * Color;\n"
		"}"
	};
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
	}
	glAttachShader(program, vertexShader);

	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile fragment shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
	}
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "aPosition");
	glBindAttribLocation(program, 1, "aTexCoord");
	glBindAttribLocation(program, 2, "aColor");

	glLinkProgram(program);
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", program);
		printProgramLog(program);
	}

	glValidateProgram(program);
}

void Shader::Use()
{
	glUseProgram(program);
}

void Shader::SetMatrix(const char *aUniformName, Cog::Matrix33f &aMatrix)
{
	GLuint location = glGetUniformLocation(program, aUniformName);
	Use();
	glUniformMatrix3fv(location, 1, GL_FALSE, &aMatrix.m11);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}