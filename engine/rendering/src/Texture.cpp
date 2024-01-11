#include "../Texture.hpp"

Texture::Texture(const char* image_dir) noexcept
{
    this->CreateTexture(image_dir);
}

Texture::~Texture() noexcept
{}

void Texture::CreateTexture(const char* image_dir) noexcept
{
    void* datas;
    BMP_infos info = bmp_load(image_dir, &datas);
    
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
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  this->width, this->height, 0, GL_BGR,  GL_UNSIGNED_BYTE, datas);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, datas);
        printf("-> nice\n");

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    free(datas);
}