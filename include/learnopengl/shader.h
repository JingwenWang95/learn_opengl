//
// Created by jingwen on 18/01/2020.
//

#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
class Shader
{
public:
    GLuint program_ID;
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        string vertexCode, fragmentCode;
        ifstream vShaderFile, fShaderFile;
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            stringstream vertexStream, fragmentStream;
            vertexStream << vShaderFile.rdbuf();
            fragmentStream << fShaderFile.rdbuf();

            vertexCode = vertexStream.str();
            fragmentCode = fragmentStream.str();

            vShaderFile.close();
            fShaderFile.close();
        }
        catch (ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");

        // shader Program
        program_ID = glCreateProgram();
        glAttachShader(program_ID, vertexShader);
        glAttachShader(program_ID, fragmentShader);
        glLinkProgram(program_ID);
        checkCompileErrors(program_ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }
    // use/activate the shader
    void use()
    {
        glUseProgram(program_ID);
    }
    // utility uniform functions
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(program_ID, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(program_ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(program_ID, name.c_str()), value);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
                "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
                "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};


#endif //LEARN_OPENGL_SHADER_H
