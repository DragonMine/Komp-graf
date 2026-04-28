#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::string loadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open " << path << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

static GLuint compileShader(const std::string& src, GLenum type, const std::string& typeName) {
    GLuint shader = glCreateShader(type);
    const char* cstr = src.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "Shader compilation error (" << typeName << "):\n" << log << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

Shader::Shader() : programID(0) {}
Shader::~Shader() { if (programID) glDeleteProgram(programID); }

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertSrc = loadFile(vertexPath);
    std::string fragSrc = loadFile(fragmentPath);
    if (vertSrc.empty() || fragSrc.empty()) return false;

    GLuint vert = compileShader(vertSrc, GL_VERTEX_SHADER, "VERTEX");
    GLuint frag = compileShader(fragSrc, GL_FRAGMENT_SHADER, "FRAGMENT");
    if (!vert || !frag) return false;

    programID = glCreateProgram();
    glAttachShader(programID, vert);
    glAttachShader(programID, frag);
    glLinkProgram(programID);
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(programID, 1024, nullptr, log);
        std::cerr << "Shader linking error:\n" << log << std::endl;
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }
    glDeleteShader(vert);
    glDeleteShader(frag);
    return true;
}

Shader& Shader::use() { glUseProgram(programID); return *this; }
void Shader::unuse() { glUseProgram(0); }
GLuint Shader::getID() { return programID; }

Shader& Shader::set(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    return *this;
}
Shader& Shader::set(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    return *this;
}
Shader& Shader::set(const std::string& name, const float* values, int count) {
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), count, values);
    return *this;
}
Shader& Shader::setMat4(const std::string& name, const float* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, matrix);
    return *this;
}