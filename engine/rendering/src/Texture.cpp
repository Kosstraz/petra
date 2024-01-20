#include "../Texture.hpp"

Texture::Texture(const char* image_dir) noexcept    :   width(0), height(0), textureID(0)
{
    this->CreateTexture(image_dir);
}

void Texture::CreateTexture(const char* image_dir) noexcept
{
    uint8* data;
    img_infos info  =   png_load(image_dir, &data);

    IF_RARELY(info.errorCode < 0)
    {
        DEBUG(TEXTURE_LOG, "Erreur 'img_load(image_dir, &data)' dans 'Texture::CreateTexture(...)'")
        printf("Code erreur : %d\n", info.errorCode);
    }
    else
    {
        this->width  = info.width;
        this->height = info.height;
        
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        if (info.bitsPerPixel == 32)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  this->width, this->height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,   this->width, this->height, 0, GL_RGB,   GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glGenerateMipmap(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0 + this->textureID);
    }

    free(data);
}

void Texture::BindToShader(const char* textureName) noexcept
{
    unsigned int textureID = global_rendering::textures[textureName];
    glActiveTexture(GL_TEXTURE0 + textureID);
    
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "TEXTURE");
    glUniform1i(unifLoc, textureID);
}

void Texture::BindToShader(uint textureID)    noexcept
{
    glActiveTexture(GL_TEXTURE0 + textureID);
    
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "TEXTURE");
    glUniform1i(unifLoc, textureID);
}

uint Texture::TakeTexture() const noexcept
{
    return (this->textureID);
}