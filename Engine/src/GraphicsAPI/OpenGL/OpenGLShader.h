//
// Created by Let'sBlend on 12/03/2024.
//

#ifndef CLOSINGIN_OPENGLSHADER_H
#define CLOSINGIN_OPENGLSHADER_H

#include "GraphicsAPI/Shader.h"

#define MAX_SHADER_TYPE 2

enum class ShaderType
{
    Properties = 0,
    Vertex = 1,
    Pixel = MAX_SHADER_TYPE
};

class OpenGLShader : public Shader
{
public:
    explicit OpenGLShader(const std::string& filePath);
    ~OpenGLShader() override;

    void Bind() override;
    void UnBind() override;
    uint32 GetID() override;

    void SetBool(bool value, const std::string &variable) override;
    void SetInt(int value, const std::string &variable) override;
    void SetFloat(float value, const std::string &variable) override;
    void SetVector2(Math::vec2 value, const std::string &variable) override;
    void SetVector3(Math::vec3 value, const std::string &variable) override;
    void SetVector4(const Math::vec4& value, const std::string &variable) override;

private:
    void ReadFromFile(std::string& source, const std::string& filePath);
    void SplitShaders(std::unordered_map<ShaderType, std::string>& sections, std::string& source);
    void ResolveSyntax(std::unordered_map<ShaderType, std::string>& sections);
    void Compile(std::unordered_map<ShaderType, std::string>& sections);
    std::string ExtractName(std::string line);

    uint32 shaderProgramID;
};
#endif //CLOSINGIN_OPENGLSHADER_H
