#include <ostream>
#include <shader.hpp>
#include "Renderer.hpp"


ShaderSource ParseShader(std::string filepath){
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){

        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    // print the shader source
    // std::cout << ss[0].str() << std::endl;

    return {ss[0].str(), ss[1].str()};
}

unsigned int CompileShaders(std::string vertexshaderstring, std::string fragmentshaderstring){
    const char* VertexShaderSource = vertexshaderstring.c_str();
    const char* FragmentShaderSource = fragmentshaderstring.c_str();

    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertexShader, 1, &VertexShaderSource, NULL));
    GLCall(glCompileShader(vertexShader));
    GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Vertex shader failed to compile");
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL));
    GLCall(glCompileShader(fragmentShader));
    GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Fragment shader failed to compile");
    }
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    GLCall(glAttachShader(shaderProgram, vertexShader));
    GLCall(glAttachShader(shaderProgram, fragmentShader));
    GLCall(glLinkProgram(shaderProgram));
    glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Failed to link Shader program");
    }

    GLCall(glUseProgram(shaderProgram));
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    return shaderProgram;

}
