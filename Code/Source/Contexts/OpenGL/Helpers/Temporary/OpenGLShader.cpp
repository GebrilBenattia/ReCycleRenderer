#include "OpenGLShader.hpp"
#include <fstream>
#include <sstream>

OpenGLShader::OpenGLShader(const std::string& _VertexPath, const std::string& _FragmentPath)
	:m_ID(0)
{
	CreateShader("C:/Users/MrHer/Desktop/ReCycle/recyclerenderer/Assets/Shaders/OpenGL/GLSL/" + _VertexPath, "C:/Users/MrHer/Desktop/ReCycle/recyclerenderer/Assets/Shaders/OpenGL/GLSL/" + _FragmentPath);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_ID);
}

const std::string OpenGLShader::ReadShaderFile(const std::string& _Path)
{
    // Retrieve the vertex/fragment source code from filePath
    std::ifstream shaderFile;
    std::stringstream shaderStream;
    // Ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open file
        shaderFile.open(_Path);
        // Read file's buffer content into stream
        shaderStream << shaderFile.rdbuf();
        // Close file handler
        shaderFile.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    // Return stream as a string
    return shaderStream.str();
}

void OpenGLShader::CreateShader(const std::string& _VertexPath, const std::string& _FragmentPath)
{
    // TODO do a proper version of the shader code loading
    std::string shaderCode;

    // Get the code from vertex shader file
    shaderCode = ReadShaderFile(_VertexPath);
    const char* vertexShaderCode = shaderCode.c_str();

    // Get the code from fragment shader file
    shaderCode = ReadShaderFile(_FragmentPath);
    const char* fragmentShaderCode = shaderCode.c_str();

    // Create shader objects
    std::vector<unsigned int> shaderObjectList;
    const unsigned int vertex = CreateShaderObject(GL_VERTEX_SHADER, vertexShaderCode, "VERTEX");
    const unsigned int fragment = CreateShaderObject(GL_FRAGMENT_SHADER, fragmentShaderCode, "FRAGMENT");

    shaderObjectList.push_back(vertex);
    shaderObjectList.push_back(fragment);
    
    m_ID = CreateShaderProgram(shaderObjectList);
    
    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void OpenGLShader::Use()
{
	glUseProgram(m_ID);
}

void OpenGLShader::SetBool(const char* _Name, bool _Value)
{
	glUniform1i(glGetUniformLocation(m_ID, _Name), _Value);
}

void OpenGLShader::SetInt(const char* _Name, int _Value)
{
	glUniform1i(glGetUniformLocation(m_ID, _Name), _Value);
}

void OpenGLShader::SetFloat(const char* _Name, float _Value)
{
	glUniform1f(glGetUniformLocation(m_ID, _Name), _Value);
}