#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFail;
	ifstream fragmentFail;
	stringstream vertexSStream;
	stringstream fragmentSStream;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	vertexFail.open(vertexPath);
	fragmentFail.open(fragmentPath);
	vertexFail.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFail.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertexFail.is_open() || !fragmentFail.is_open())
		{
			throw exception("Open file error");
		}
		vertexSStream << vertexFail.rdbuf();
		fragmentSStream << fragmentFail.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexShaderSource = vertexString.c_str();
		fragmentShaderSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertex, 1, &vertexShaderSource, NULL);
		glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
		glCompileShader(vertex);
		glCompileShader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
}

void Shader::use()
{
	glUseProgram(ID);
}