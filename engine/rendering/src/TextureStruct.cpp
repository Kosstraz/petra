#include <rendering/TextureStruct.hpp>

ArrayForTexture global_textures = ArrayForTexture();

const uint32& get_global_texture_val(const char* _keyVal)   // !inutile
{
    ArrayForTexture::const_iterator ite = global_textures.begin();
    while (++ite != global_textures.end())
        if (strcmp(_keyVal, ite->first) == 0)
            return (ite->second);
    throw(ite->first);
}