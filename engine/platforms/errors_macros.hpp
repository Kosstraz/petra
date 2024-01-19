#pragma once

#define return_error(msg, intLog)  { printf(msg); printf("\nCode erreur : %d\n", intLog); return(intLog); }

    // Generics
#define  GENERIC_ERROR          -(0x001)
#define  BAD_MALLOC             -(0x002)

    // GLFW errors
#define  GLFWINIT_FAILED        -(0x003)
#define  GLADLOADER_FAILED      -(0x004)
#define  WINDOWNnullptr_FAILED  -(0x005)

    // FileManager errors
#define  FILE_NULL              -(0x006)
#define  NOT_SEEK               -(0x007)
#define  NOT_CLOSED             -(0x008)
#define  PUTC_NOT_OK            -(0x009)

    // BMP errors
#define  BMP_ERROR              -(0x00A)
#define  BMP_BAD_COMPRESSION    -(0x00B)

    // PNG errors
#define  PNG_ERROR              -(0x00C)
#define  PNG_BAD_COMPRESSION    -(0x00D)

    // JSON errors
#define JSON_BAD_OPENNING       -(0x00E)
#define JSON_BAD_SEEKING        -(0x00F)
#define JSON_NOT_CLOSED         -(0x010)
#define JSON_ERROR_FILE_FORMAT  -(0x011)

    // SHADER errors
#define SHADER_BAD_GUESSING     -(0x012)