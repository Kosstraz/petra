#pragma once

#include <cstdio>

#define DEBUG(TYPE_LOG, msg) printf(TYPE_LOG); printf(msg); printf("\n");
#define DEBUG_GL()    GLenum error = glad_glGetError();   if (error != GL_NO_ERROR)   { printf(OGL_LOG) ;printf("Error code : %d\n", error); }

#define TEST_LOG   ("[TEST      LOG] ")
#define OGL_LOG    ("[OpenGL    LOG] ")
#define CORE_LOG   ("[CORE      LOG] ")
#define SCENE_LOG  ("[SCENE     LOG] ")
#define SHADER_LOG ("[SHADER    LOG] ")
#define OBJECT_LOG ("[OBJECT    LOG] ")
#define MATHS_LOG  ("[MATHS     LOG] ")