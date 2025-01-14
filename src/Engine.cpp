#include "Engine.hpp"
#include <stdexcept>

Engine::Engine(){

    /* Initialize the library */
    if (!glfwInit())
        throw std::runtime_error("Failed to Init GLFW");
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
        throw std::runtime_error("Failed to create GLFW window");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        throw std::runtime_error("Failed to initialize OpenGL context through gladLoadGLLoader");
    }

    int indices[] = {
	0, 1, 3,
	1, 2, 3,
    };

    float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ShaderSource shaders = ParseShader("res/shaders/basic.shader");
    
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
    std::cout << "Engine terminated successfully" << std::endl;
}

Engine::~Engine(){
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);

}

void Engine::framebuffer_size_callback(GLFWwindow * window, int width, int height){
    int fbSizeX, fbSizeY;
    glfwGetFramebufferSize(window, &fbSizeX, &fbSizeY);
    glViewport(0, 0, fbSizeX, fbSizeY);

    std::cout << "Framebuffer size: " << fbSizeX << "x" << fbSizeY << std::endl;
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
