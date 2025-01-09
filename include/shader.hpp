#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

struct ShaderSource{
	const std::string VertexSource;
	const std::string FragmentSource;
};

ShaderSource ParseShader(std::string filepath);
unsigned int CompileShaders(std::string vertexshaderstring, std::string fragmentshaderstring);
