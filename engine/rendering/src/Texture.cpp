#include "../Texture.hpp"

Texture::Texture(const char* image_dir) noexcept    :   width(0), height(0), textureID(0)
{
    this->CreateTexture(image_dir);
}

void Texture::CreateTexture(const char* image_dir) noexcept
{
    unsigned char* data = nullptr;
    img_infos info      = bmp_load(image_dir, &data);

    IF_RARELY(info.errorCode < 0)
    {
        DEBUG(TEXTURE_LOG, "Erreur dans 'CreateTexture(...)' avec 'bmp_load'")
        printf("Code erreur : %d\n", info.errorCode);
    }
    else
    {
        this->width  = info.width;
        this->height = info.height;
        
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        if (info.bitsPerPixel == 32)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  this->width, this->height, 0, GL_BGRA,  GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,   this->width, this->height, 0, GL_BGR,   GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
    }

    free(data);
}

void Texture::BindToShader() const noexcept
{
    glUseProgram(Handle::shadersProgram[0]);

    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "TEXTURE");
    glUniform1i(unifLoc, 0);
}

uint Texture::TakeTexture() const noexcept
{
    return (this->textureID);
}