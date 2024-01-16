#ifndef CONVERTFULLSHADERTOGLSL_H
#define CONVERTFULLSHADERTOGLSL_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "FileManager.h"
#include <platforms/errors_macros.hpp>

    // (si MAX_FILE_SIZE = 0) = DEFAULT_FILE_SIZE (2048)
    // Conversion .VFS.hlsl -> .vert.hlsl & .frag.hlsl | pour une pleine compatibilité avec OpenGL
int ConvertShaderExtension_GLSL(const char* FVS_fileName, unsigned int MAX_FILE_SIZE);

    // Ne pas utiliser si vous ne voulez pas parser un fichier .VFS.glsl, utilisation extrêmement spécifique
void _parcingVFS(const char* vfs_content, char** new_content, const char* BEGIN_KEYWORD, unsigned int MAX_FILE_SIZE);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif