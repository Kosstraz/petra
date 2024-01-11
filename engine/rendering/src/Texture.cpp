#include "../Texture.hpp"

Texture::Texture(const char* image_dir) noexcept
{
    this->CreateTexture(image_dir);
}

Texture::~Texture() noexcept
{}

void Texture::CreateTexture(const char* image_dir) noexcept
{
    unsigned char* data = ((unsigned char*)0);
    BMP_infos info = bmp_load(image_dir, &data);

    if (info.errorCode < 0)
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
        if (info.bitsPerPixel == 24)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  info.width, info.height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        printf("-> nice\n");

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    free(data);
}