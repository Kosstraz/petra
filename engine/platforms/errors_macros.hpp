#pragma once

#define return_error(msg, intLog)  { printf(msg); printf("\nCode erreur : %d\n", intLog); return(intLog); }

    // Generics
#define  GENERIC_ERROR          -(0x001)
#define  BAD_MALLOC             -(0x002)

    // GLFW errors
#define  GLFWINIT_FAILED        -(0x003)
#define  GLADLOADER_FAILED      -(0x004)
#define  WINDOWNnullptr_FAILED  -(0x005)

    // SHADER errors
#define  SHADER_BAD_GUESSING    -(0x006)

    // FileManager errors
#define  FILE_NULL              -(0x007)
#define  NOT_SEEK               -(0x008)
#define  NOT_CLOSED             -(0x009)
#define  PUTC_NOT_OK            -(0x00A)

    // IMAGE_FILE errors
#define  BAD_FILE_FORMAT        -(0x00B)
#define  NOT_IMG_FILE_SUPPORTED -(0x00C)
#define  DECOMPRESSION_FILE_ERR -(0x00D)
#define  IMAGE_NOT_FOUND        -(0x00E)

    // BMP errors
#define  BMP_ERROR              -(0x00F)
#define  BMP_BAD_COMPRESSION    -(0x010)

    // PNG errors
#define  PNG_ERROR              -(0x011)
#define  PNG_BAD_COMPRESSION    -(0x012)

    // JSON errors
#define  JSON_BAD_OPENNING      -(0x013)
#define  JSON_BAD_SEEKING       -(0x014)
#define  JSON_NOT_CLOSED        -(0x015)
#define  JSON_ERROR_FILE_FORMAT -(0x016)