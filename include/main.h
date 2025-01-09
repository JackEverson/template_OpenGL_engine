#include <cstddef>
#include <iostream>

#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

// int win_width = 3840;
// int win_height = 2160;
int win_width = 1920;
int win_height = 1080;
// int win_width = 640;
// int win_height = 480;

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3,
};

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

const char *VertexShaderSource = 
"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *FragmentShaderSource = 
"#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow *window);
