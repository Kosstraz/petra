#pragma once

#define return_error(msg, intLog)  { printf(msg); printf("\nCode erreur : %d\n", intLog); return(intLog); }

#define  GLFWINIT_FAILED        -(0x002)
#define  GLADLOADER_FAILED      -(0x003)
#define  WINDOWNnullptr_FAILED  -(0x004)

#define  FILE_NULL     -(0x005)
#define  NOT_SEEK      -(0x006)
#define  NOT_CLOSED    -(0x007)
#define  PUTC_NOT_OK   -(0x008)

#define  BMP_ERROR            -(0x009)
#define  BMP_BAD_COMPRESSION  -(0x00A)