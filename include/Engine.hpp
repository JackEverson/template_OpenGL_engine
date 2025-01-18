#pragma once
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "shader.hpp"

class Engine{
public:
    
    // window stuff
    GLFWwindow* _window;
    int win_width = 1920;
    int win_height = 1080;

    // buffer pointers
    unsigned int VAO;
    
    Engine();
    ~Engine();

    void framebuffer_size_callback(GLFWwindow * window, int width, int height);
    void processInput(GLFWwindow *window);
};


