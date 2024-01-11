#ifndef PETRA_TEXTURE_HPP
#define PETRA_TEXTURE_HPP

#include <glad/glad.h>

#include <platforms/logs_macros.hpp>

#define IMAGES_BMP
    #include <C/petra_images.h>

class Texture final
{
public:
    Texture(const char* image_dir) noexcept;
   ~Texture() noexcept;

    void CreateTexture(const char* image_dir) noexcept;

    unsigned int width, height;

private:
    unsigned int bytesSize;
    unsigned int textureID;
};

#endif