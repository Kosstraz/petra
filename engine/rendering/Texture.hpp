#ifndef PETRA_TEXTURE_HPP
#define PETRA_TEXTURE_HPP

#include <glad/glad.h>

#include <core/Handle.hpp>
#include <platforms/logs_macros.hpp>

#include <C/TextureStruct.h>

#define IMAGES_BMP
    #include <C/petra_images.h>

class Texture final
{
public:
    Texture(const char* image_dir)  noexcept;
   ~Texture()                       noexcept = default;

    void        CreateTexture(const char* image_dir)    noexcept;
    static void BindToShader (const char* textureName)  noexcept;

    uint        TakeTexture()                   const   noexcept;

    uint width, height;
private:
    uint textureID;
};

#endif