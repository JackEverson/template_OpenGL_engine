#include "Engine.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"



Engine::Engine(){
    /* Initialize the library */
    if (!glfwInit())
        throw std::runtime_error("Failed to Init GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f// top left 
    };

    unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3,
    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;
    VertexArray va;
    VertexBuffer vb(vertices, 4 * 5 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    
    // Shader shader ("res/shaders/basic.shader");
    Shader shader ("res/shaders/basictexture.shader");
    shader.Bind();

    // Texture texture("res/textures/container.jpg");
    Texture texture("res/textures/container2.png");
    texture.Bind();
    
    framebuffer_size_callback(_window, win_width, win_height);

    float increment = 0.01f;
    float color = 0.0f;

    std::cout << "starting main program loop" << std::endl;
    /* Loop until the user closes the window */
   while(glfwWindowShouldClose(_window) == 0 ){
        int w, h;
        glfwGetWindowSize(_window, &w, &h);
        framebuffer_size_callback(_window, w, h);

        if (color > 1.0f)
            increment = -0.01f;
        else if (color <= 0.0f)
            increment = 0.01f;

        color += increment;

        renderer.Clear();
        shader.SetUniform3f("aColor", color, 0.0f, 0.0f);
        shader.SetUniform3f("aLoc", locx, locy, 0.0f);
        shader.SetUniform1i("atexCoord", 0);

        renderer.Draw(va, ib, shader);
        
        processInput(_window);

        GLCall(glfwSwapBuffers(_window));
        glfwPollEvents();
   }


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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        locy += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        locy -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        locx -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        locx += 0.01f;
    }
    

}
