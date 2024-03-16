//
// Created by Let'sBlend on 15/03/2024.
//

#include "OpenGLTextures.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"

OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, colorChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &colorChannels, 0);
    if(data == nullptr)
        std::cout << "Failed to load texture from file: " << filePath << std::endl; // TODO: Assertion here

    GLint channels[4] = {GL_RED, GL_RG, GL_RGB, GL_RGBA};
    glTexImage2D(GL_TEXTURE_2D, 0, channels[colorChannels - 1], width, height, 0, channels[colorChannels - 1], GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &textureID);
}

void OpenGLTexture2D::Bind(uint32 slot)
{
    glBindTextureUnit(slot, textureID);
}

void OpenGLTexture2D::UnBind(uint32 slot)
{
    glBindTextureUnit(slot, 0);
}

uint32 OpenGLTexture2D::GetID()
{
    return textureID;
}
