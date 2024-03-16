//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_SHADER_H
#define CLOSINGIN_SHADER_H


class Shader
{
public:
    Shader() = default;
    virtual ~Shader() = default;

    static Ref<Shader> Create(const std::string& filePath);

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    virtual uint32 GetID() = 0;

    virtual void SetBool(bool value, const std::string &variable) = 0;
    virtual void SetInt(int value, const std::string &variable) = 0;
    virtual void SetFloat(float value, const std::string &variable) = 0;
    virtual void SetVector2(Math::vec2 value, const std::string &variable) = 0;
    virtual void SetVector3(Math::vec3 value, const std::string &variable) = 0;
    virtual void SetVector4(const Math::vec4& value, const std::string &variable) = 0;
};


#endif //CLOSINGIN_SHADER_H
