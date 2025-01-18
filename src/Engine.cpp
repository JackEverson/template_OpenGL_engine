#include "Engine.hpp"
#include "GLFW/glfw3.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "Renderer.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


Engine::Engine(){
    /* Initialize the library */
    if (!glfwInit())
        throw std::runtime_error("Failed to Init GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                                                 //
    // /* Create a windowed mode window and its OpenGL context */
    //

    int monitor_count;
    GLFWmonitor** _monitors = glfwGetMonitors(&monitor_count);
    if (!monitor_count){
        std::cout << "GLFWmonitor found monitors to be null" << std::endl;
        throw std::runtime_error("GLFWMonitor found monitors to be null");
    }
    std::cout << "GLFWmonitors has found " << monitor_count << " monitors" << std::endl;
    for (int i = 0; i < monitor_count; i++){
        const GLFWvidmode* mode = glfwGetVideoMode(_monitors[i]);
        std::cout << "Monitor " << i << ", " << _monitors[i] << ", has resolution " << mode->width << "x" << mode->height << std::endl;
    }

    // GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    // std::cout << "Using monitor: " << pMonitor << std::endl;

    // GLFWgetmonitor

        

    _window = glfwCreateWindow(win_width, win_height, "Template", NULL, NULL);
    // _window = glfwCreateWindow(win_width, win_height, "Template", pMonitor, NULL);
    
    if (!_window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        throw std::runtime_error("Failed to initialize OpenGL context through gladLoadGLLoader");
    }

    const float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3,
    };

    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    VertexBuffer vb(vertices, 4 * 3 * sizeof(float));
    IndexBuffer ib(indices, 6);

    ShaderSource shaders = ParseShader("res/shaders/basic.shader");
    unsigned int shaderProgram = CompileShaders(shaders.VertexSource, shaders.FragmentSource);

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    
    framebuffer_size_callback(_window, win_width, win_height);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    bool goingUp = true;
    float color = 0.0f;

    std::cout << "starting main program loop" << std::endl;
    /* Loop until the user closes the window */
   while(glfwWindowShouldClose(_window) == 0 )
    {
        int w, h;
        glfwGetWindowSize(_window, &w, &h);
        framebuffer_size_callback(_window, w, h);

        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        if (color > 1.0f)
            goingUp = false;
        else if (color < 0.0f)
            goingUp = true;

        if (goingUp)
            color += 0.01f;
        else
            color -= 0.01f;

        unsigned int box_color = glGetUniformLocation(shaderProgram, "aColor");
        glUniform3f(box_color, 1.0f, 0.0f, color);
        
        processInput(_window);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        GLCall(glUseProgram(shaderProgram));
        vb.Bind();
        ib.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        GLCall(glfwSwapBuffers(_window));
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(_window);
    glfwTerminate();
    std::cout << "Engine terminated successfully" << std::endl;
}

Engine::~Engine(){
}

void Engine::framebuffer_size_callback(GLFWwindow * window, int width, int height){
    int fbSizeX, fbSizeY;
    glfwGetFramebufferSize(window, &fbSizeX, &fbSizeY);
    glViewport(0, 0, fbSizeX, fbSizeY);

    // std::cout << "Framebuffer size: " << fbSizeX << "x" << fbSizeY << std::endl;
    // glViewport(0, 0, width, height);
}

void Engine::processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        std::cout << "left click detected at " << xpos << "x" << ypos << std::endl;
    }
}
