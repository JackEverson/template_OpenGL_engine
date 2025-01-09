#include "main.h"
#include "shader.hpp"

#include "GLFW/glfw3.h"
#include <GL/gl.h>

#include <stdexcept>

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                                                 //
    // /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(win_width, win_height, "test", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    ShaderSource shaders = ParseShader("res/shaders/basic.shader");

    std::cout << "#####v" << std::endl << shaders.VertexSource << std::endl;
    std::cout << "#####f" << std::endl << shaders.FragmentSource << std::endl;

    
    unsigned int shaderProgram = CompileShaders(shaders.VertexSource, shaders.FragmentSource);
    
    framebuffer_size_callback(window, win_width, win_height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    
    std::cout << "starting main program loop" << std::endl;
    /* Loop until the user closes the window */
   while(glfwWindowShouldClose(window) == 0 )
    {
        // int w, h;
        // glfwGetWindowSize(window, &w, &h);
        // framebuffer_size_callback(window, w, h);

        glClear(GL_COLOR_BUFFER_BIT);
        
        processInput(window);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    std::cout << "Program finished successfully" << std::endl;
    return 0;
}

// resize window event
void framebuffer_size_callback(GLFWwindow * window, int width, int height){
    int fbSizeX, fbSizeY;
    glfwGetFramebufferSize(window, &fbSizeX, &fbSizeY);
    glViewport(0, 0, fbSizeX, fbSizeY);

    std::cout << "Framebuffer size: " << fbSizeX << "x" << fbSizeY << std::endl;
    // glViewport(0, 0, width, height);
}

// process user input
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        std::cout << "left click detected at " << xpos << "x" << ypos << std::endl;
    }
        

}
