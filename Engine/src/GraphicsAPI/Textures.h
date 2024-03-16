//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_TEXTURES_H
#define CLOSINGIN_TEXTURES_H

class Texture2D
{
public:
    Texture2D() = default;
    virtual ~Texture2D() = default;

    static Ref<Texture2D> Create(const std::string& filePath);

    virtual void Bind(uint32 slot) = 0;
    virtual void UnBind(uint32 slot) = 0;
    virtual uint32 GetID() = 0;
};


#endif //CLOSINGIN_TEXTURES_H
