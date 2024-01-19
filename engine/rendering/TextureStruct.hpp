#ifndef PETRA_TEXTURESTRUCT_HPP
#define PETRA_TEXTURESTRUCT_HPP

#include <C/petra_images.h>
#include <unordered_map>

typedef std::unordered_map<const char*, uint32> ArrayForTexture;

namespace global_rendering
{
    static inline ArrayForTexture textures = ArrayForTexture();
}

#endif