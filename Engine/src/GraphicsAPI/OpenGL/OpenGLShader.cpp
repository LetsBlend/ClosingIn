//
// Created by Let'sBlend on 12/03/2024.
//

#include "OpenGLShader.h"
#include "glad/glad.h"

/////////////////////////////////////////////////////////////////////
// Vertex & Pixel Shader
/////////////////////////////////////////////////////////////////////

OpenGLShader::OpenGLShader(const std::string& filePath)
{
    std::string source;
    std::unordered_map<ShaderType, std::string> sections;
    ReadFromFile(source, filePath);
    SplitShaders(sections, source);
    ResolveSyntax(sections);
    Compile(sections);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(shaderProgramID);
}

void OpenGLShader::ReadFromFile(std::string &source, const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) // TODO: Assertion here
    {
        std::cout << "Could not open the file: " << "'" << filePath << "'" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    source = buffer.str();

    file.close();
}

void OpenGLShader::SplitShaders(std::unordered_map<ShaderType, std::string> &sections, std::string &source)
{
    std::istringstream input(source);
    std::string currentLine;
    ShaderType type;

    while (std::getline(input, currentLine))
    {
        if (currentLine.find("#pragma properties") != std::string::npos)
        {
            type = ShaderType::Properties;
            sections[type] = "";
        } else if (currentLine.find("#pragma vertex") != std::string::npos)
        {
            type = ShaderType::Vertex;
            sections[type] = "";
        } else if (currentLine.find("#pragma pixel") != std::string::npos)
        {
            type = ShaderType::Pixel;
            sections[type] = "";
        } else
        {
            sections[type] += currentLine + "\n";
        }
    }
}

void OpenGLShader::ResolveSyntax(std::unordered_map<ShaderType, std::string> &sections)
{
    // Resolving Entry Point
    size_t pos;
    pos = sections[ShaderType::Vertex].find("vert");
    if (pos != std::string::npos)
        sections[ShaderType::Vertex].replace(pos, 4, "main");

    pos = sections[ShaderType::Pixel].find("pixel");
    if (pos != std::string::npos)
        sections[ShaderType::Pixel].replace(pos, 5, "main");

    // Resolving Properties/Uniforms
    std::vector<std::string> properties;
    std::istringstream input(sections[ShaderType::Properties]);
    std::string currentLine;
    while (std::getline(input, currentLine))
    {
        if(!currentLine.empty())
            properties.push_back(currentLine);
    }

    for (int i = 1; i <= MAX_SHADER_TYPE; i++)
    {
        for(const std::string& prop : properties)
        {
            std::string extracted = ExtractName(prop);
            if(extracted.empty())
                std::cout << "Couldn't extract variable name out of property!" << std::endl; // TODO: Assertion here

            size_t pos = sections[(ShaderType)i].find(extracted);
            if(pos != std::string::npos)
                sections[(ShaderType)i].insert(0, "uniform " + prop + "\n");
        }
    }

    // Resolving Version
    sections[ShaderType::Vertex].insert(0, "#version 460 core\n");
    sections[ShaderType::Pixel].insert(0, "#version 460 core\n");

    std::cout << sections[ShaderType::Vertex] << std::endl;
    std::cout << sections[ShaderType::Pixel] << std::endl;
}

void OpenGLShader::Compile(std::unordered_map<ShaderType, std::string> &sections)
{
    shaderProgramID = glCreateProgram();

    GLenum shaderType[MAX_SHADER_TYPE + 1] = {0, GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
    uint32 shaderIDs[MAX_SHADER_TYPE + 1];
    for(int i = 1; i <= MAX_SHADER_TYPE; i++)
    {
        if(sections[(ShaderType)i].empty())
            continue;

        const char *vertexShaderSource = sections[(ShaderType)i].c_str();

        uint32 shaderID = glCreateShader(shaderType[i]);
        glShaderSource(shaderID, 1, &vertexShaderSource, nullptr);
        glCompileShader(shaderID);

        int success;
        char shaderLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 512, nullptr, shaderLog);
            std::cout << "[ERROR]: Shader did not compile: " << shaderLog << std::endl;
        }

        glAttachShader(shaderProgramID, shaderID);
        shaderIDs[i] = shaderID;
    }
    glLinkProgram(shaderProgramID);

    int success;
    char programLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, programLog);
        std::cout << "[ERROR]: Shader did not compile: " << programLog << std::endl; //TODO: Assertion here

        glDeleteProgram(shaderProgramID);
        for(int i = 1; i <= MAX_SHADER_TYPE; i++)
            glDeleteShader(shaderIDs[i]);
    }

    for(int i = 1; i <= MAX_SHADER_TYPE; i++)
    {
        glDetachShader(shaderProgramID, shaderIDs[i]);
        glDeleteShader(shaderIDs[i]);
    }
}

std::string OpenGLShader::ExtractName(std::string line)
{
    size_t semicolon = line.find(';');
    if(semicolon == std::string::npos)
        return "";

    size_t endPos = semicolon;
    while(endPos > 0 && std::isspace(line[endPos - 1]))
        endPos--;

    size_t startPos = endPos - 1;
    while(startPos > 0 && !std::isspace(line[startPos]))
        startPos--;
    startPos++;

    return line.substr(startPos, endPos - startPos);
}

void OpenGLShader::Bind()
{
    glUseProgram(shaderProgramID);
}

void OpenGLShader::UnBind()
{
    glUseProgram(0);
}

uint32 OpenGLShader::GetID()
{
    return shaderProgramID;
}

void OpenGLShader::SetBool(bool value, const std::string &variable)
{
    Bind();
    int location = glGetUniformLocation(shaderProgramID, variable.c_str());
    glUniform1i(location, value);
    UnBind();
}

void OpenGLShader::SetInt(int value, const std::string &variable)
{
    Bind();
    int location = glGetUniformLocation(shaderProgramID, variable.c_str());
    glUniform1i(location, value);
    UnBind();
}

void OpenGLShader::SetFloat(float value, const std::string &variable)
{
    Bind();
    int location = glGetUniformLocation(shaderProgramID, variable.c_str());
    glUniform1f(location, value);
    UnBind();
}

void OpenGLShader::SetVector2(Math::vec2 value, const std::string &variable)
{
    Bind();
    int location = glGetUniformLocation(shaderProgramID, variable.c_str());
    glUniform2f(location, value.x, value.y);
    UnBind();
}

void OpenGLShader::SetVector3(Math::vec3 value, const std::string &variable)
{
    Bind();
    int location = glGetUniformLocation(shaderProgramID, variable.c_str());
    glUniform3f(location, value.x, value.y, value.z);
    UnBind();
}

void OpenGLShader::SetVector4(const Math::vec4 &value, const std::string &variable)
{
    Bind();
    int location = glGetUniformLocation(shaderProgramID, variable.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
    UnBind();
}