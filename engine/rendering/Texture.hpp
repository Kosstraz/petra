#ifndef PETRA_TEXTURE_HPP
#define PETRA_TEXTURE_HPP

#include <glad/glad.h>

#include <core/Handle.hpp>
#include <platforms/logs_macros.hpp>

#include <rendering/TextureStruct.hpp>

#define IMAGES_BMP
    #include <C/petra_images.h>

class Texture final
{
public:
    Texture(const char* image_dir)  noexcept;
   ~Texture()                       noexcept = default;

    void        CreateTempTexture(const char* image_dir)    noexcept;
    
    static uint32   CreateTexture(const char* image_dir  )  noexcept;
    static void     BindToShader (const char* textureName)  noexcept;
    static void     BindToShader (uint32        textureID)  noexcept;

    uint32      TakeTexture()                   const   noexcept;

    uint32 width, height;
private:
    uint32 textureID;
};

#endif