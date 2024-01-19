#pragma once

#include <cstdio>

    // To print in local terminal
#define DEBUG(TYPE_LOG, msg) {printf(TYPE_LOG); printf(msg); printf("\n");}
#define DEBUG_GL()    unsigned int error = glad_glGetError();   if (error != GL_NO_ERROR)   { printf(OGL_LOG) ;printf("Error code : %d\n", error); }

    // Recorder
#define INIT_RECORD       Chrono chrono_recorder_macro;
#define RECORD            chrono_recorder_macro.Start();
#define STOP_RECORD       chrono_recorder_macro.Stop();    EXEC_TIME(chrono_recorder_macro.GetTime())
#define EXEC_TIME(value)  {printf("--- Temps d'execution --- >> %I64d ms\n", value); printf("\n");}

    // Constexpr char* log
#define TEST_LOG    ("[TEST      LOG] ")
#define OGL_LOG     ("[OpenGL    LOG] ")
#define CORE_LOG    ("[CORE      LOG] ")
#define SCENE_LOG   ("[SCENE     LOG] ")
#define SHADER_LOG  ("[SHADER    LOG] ")
#define TEXTURE_LOG ("[TEXTURE   LOG] ")
#define OBJECT_LOG  ("[OBJECT    LOG] ")
#define MATHS_LOG   ("[MATHS     LOG] ")