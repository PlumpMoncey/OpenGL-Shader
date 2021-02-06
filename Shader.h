#pragma once
#include <string>
using namespace std;
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	string vertexString;
	string fragmentString;
	//const char* vertexShaderSource;
	//const char* fragmentShaderSource;
	unsigned int ID;	//Shader Program ID
};

