#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader(const std::string& vertex, const std::string& fragment, const std::string& geometry, const std::string& compute, const std::string& Tesselation)
{
    load(vertex, fragment, geometry, compute, Tesselation);
}

void Shader::load(const std::string& vertex, const std::string& fragment, const std::string& geometry, const std::string& compute, const std::string& Tesselation)
{
    if (vertex.empty() || fragment.empty())
    {
        std::cout << "Vertex or Fragment shader is NULL." << std::endl;
        return;
    }

    std::ifstream vertexFile(vertex);
    std::ifstream fragmentFile(fragment);

    if (!vertexFile.is_open())
    {
        std::cout << "Failed to open vertex shader. Exiting" << std::endl;
        return;
    }

    if (!fragmentFile.is_open())
    {
        std::cout << "Failed to open fragment shader. Exiting" << std::endl;
        return;
    }

    std::stringstream oss;

    oss << vertexFile.rdbuf();
    const std::string vertexString = oss.str();

    const char* vertexSource = vertexString.c_str();

    unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexSource, nullptr);
    glCompileShader(vertexID);

    char infoLog[512];
    int success;
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cout << "Failed to compile vertex shader." << std::endl
            << "Error Message: " << infoLog << std::endl;
        return;
    }
    
    std::string fragmentString;
    oss.str(std::string());

    oss << fragmentFile.rdbuf();
    fragmentString = oss.str();

    const char* fragmentSource = fragmentString.c_str();

    unsigned int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cout << "Failed to compile fragment shader." << std::endl
            << "Error Message: " << infoLog << std::endl;
        return;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Failed to compile vertex shader." << std::endl
            << "Error Message: " << infoLog << std::endl;
        return;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return;
}


void Shader::setMat4f(const std::string& name, glm::mat4 input)
{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(input));
}

void Shader::setNum1i(const std::string& name, int v0)
{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    glUniform1i(loc, v0);
}

void Shader::setFloat1f(const std::string& name, float v0)
{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    glUniform1f(loc, v0);
}

void Shader::setvec3f(const std::string& name, glm::vec3 input)
{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(input));
}
