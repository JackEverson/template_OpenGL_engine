#pragma once
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

// #define ASSERT(x) if (!(x)) __debugbreak(); // for MSVC 
#define ASSERT(x) if (!(x)) std::cout << "OpenGL Error" << std::endl;

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
