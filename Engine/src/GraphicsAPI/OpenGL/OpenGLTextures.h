//
// Created by Let'sBlend on 15/03/2024.
//

#ifndef CLOSINGIN_OPENGLTEXTURES_H
#define CLOSINGIN_OPENGLTEXTURES_H

#include "GraphicsAPI/Textures.h"

class OpenGLTexture2D : public Texture2D
{
public:
    explicit OpenGLTexture2D(const std::string& filePath);
    ~OpenGLTexture2D() override;

    void Bind(uint32 slot) override;
    void UnBind(uint32 slot) override;
    uint32 GetID() override;
private:
    uint32 textureID;
};


#endif //CLOSINGIN_OPENGLTEXTURES_H
