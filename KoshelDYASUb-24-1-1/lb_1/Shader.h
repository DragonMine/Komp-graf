#pragma once
#include <string>
#include <unordered_map>
#include "GL/glew.h"

class Shader {
public:
    // Конструктор загружает и компилирует шейдеры из файлов
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Активировать программу
    void Use() const;

    // Установка uniform-переменных (перегрузки для разных типов)
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, float v1, float v2) const;               // vec2
    void SetUniform(const std::string& name, float v1, float v2, float v3) const;     // vec3
    void SetUniform(const std::string& name, float v1, float v2, float v3, float v4) const; // vec4
    void SetUniform(const std::string& name, const float* mat4, bool transpose = false) const; // mat4

private:
    GLuint programID_;
    mutable std::unordered_map<std::string, GLint> uniformLocationCache_;

    // Вспомогательные функции
    std::string LoadFile(const std::string& path);
    GLuint CompileShader(GLenum type, const std::string& source);
    void CheckCompileErrors(GLuint shader, const std::string& type);
    void CheckLinkErrors(GLuint program);
    GLint GetUniformLocation(const std::string& name) const;
};