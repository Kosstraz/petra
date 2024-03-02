#ifndef PETRA_TEXTURESTRUCT_HPP
#define PETRA_TEXTURESTRUCT_HPP

#include <C/petra_images.h>
#include <unordered_map>

typedef std::unordered_map<const char*, uint32> ArrayForTexture;

extern ArrayForTexture global_textures;

const uint32& get_global_texture_val(const char* _keyVal);  // !inutile

#endif