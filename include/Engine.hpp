#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

class Engine{
public:
    
    // window stuff
    GLFWwindow* window;
    int win_width = 1920;
    int win_height = 1080;

    // buffer pointers
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    
    Engine();
    ~Engine();

    void framebuffer_size_callback(GLFWwindow * window, int width, int height);
    void processInput(GLFWwindow *window);


};


