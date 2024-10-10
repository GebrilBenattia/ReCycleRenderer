#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

class OpenGLShader
{
private:

	int m_ID;

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(const unsigned int shader, const char* type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    const unsigned int CreateShaderObject(const GLenum _ShaderProgramType, const char* _ShaderCode, const char* _ShaderTypeName)
    {
        // Create an empty shader object, represented by the 'shader' variable (unsigned int).
        unsigned int shader = glCreateShader(_ShaderProgramType);

        // Assign the source code for the shader to the shader object.
        glShaderSource(shader, 1, &_ShaderCode, NULL);

        // Compile the vertex shader to check it for errors and translate it into GPU instructions.
        glCompileShader(shader);

        // Check for compilation errors specific to the vertex shader.
        CheckCompileErrors(shader, _ShaderTypeName);

        return shader;
    }

    const int CreateShaderProgram(const std::vector<unsigned int> _ShaderObjectList)
    {
        // Create a shader program (ID) to link both the vertex and fragment shaders.
        // A shader program encapsulates multiple shaders and is what the GPU will use to execute the shaders.
        int ID = glCreateProgram();

        // Attach the compiled shader objects to the shader program.
        for (int i = 0; i < _ShaderObjectList.size(); i++) {
            glAttachShader(ID, _ShaderObjectList[i]);
        }

        // Link the shader program, which combines both shaders and prepares them for execution.
        glLinkProgram(ID);

        // Check for linking errors in the shader program.
        CheckCompileErrors(ID, "PROGRAM");

        return ID;
    }

public:

	OpenGLShader(const std::string& _VertexPath, const std::string& _FragmentPath);
    ~OpenGLShader();

    const std::string ReadShaderFile(const std::string& _Path);

    void CreateShader(const std::string& _VertexPath, const std::string& _FragmentPath);

	void Use();

	void SetBool(const char* _Name, bool _Value);
	void SetInt(const char* _Name, int _Value);
	void SetFloat(const char* _Name, float _Value);
};