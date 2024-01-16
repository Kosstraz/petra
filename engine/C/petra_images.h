#ifndef PETRA_IMAGES_H
#define PETRA_IMAGES_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platforms/errors_macros.hpp"
#include "platforms/types_macros.hpp"

#define IMAGES_ALL
#define IMAGES_BMP

    /*//////////////*/
    //  FONDAMENTAL //
    /*//////////////*/

#pragma pack(push, 1)
    typedef struct img_infos {
        int8   errorCode;
        uint32 datasOffset;
        uint32 fileSize;
        int32  width;
        int32  height;
        uint16 bitsPerPixel;
        uint32 compression;
        uint32 imageSize;

    }   img_infos;
#pragma pack(pop)

void init_img_infos(img_infos* infos);


    /*////////////*/
    //  FONCTIONS //
    /*////////////*/

    // Toutes les fonctions et structures liées aux fichiers images en général
#ifdef  IMAGES_ALL
    #define IMAGES_BMP
    #define IMAGES_PNG
#endif  // !ALL

    // Toutes les fonctions et structures liées aux fichiers images .bmp
#ifdef  IMAGES_BMP
    #pragma pack(push, 1)
    typedef struct BMP_header {
        char   signature[2];
        uint32 fileSize ;
        uint16 reserved1;
        uint16 reserved2;
        uint32 datasOffset;

            /// DIP header
        uint32 headerSize;
        int32  width;
        int32  height;
        uint16 colorPlanes;
        uint16 bitsPerPixel;
        uint32 compression;
        uint32 imageSize;
        int32  horizontalResolution;
        int32  verticalResolution;
        uint32 colorsInColorPalette;
        uint32 NbImportantColors;

    }   BMP_header;
    #pragma pack(pop)
int8        bmp_header  (const char* file_name,                 img_infos* infos);
int8        bmp_datas   (const char* file_name, uint8** buffer, img_infos* infos);
img_infos   bmp_load    (const char* file_name, uint8** buffer                  );
#endif  // !BMP




#ifdef  IMAGES_PNG
int8        png_header  (const char* file_name,                  img_infos* infos);
int8        png_datas   (const char* file_name, uint8** buffer,  img_infos* infos);
img_infos   png_load    (const char* file_name, uint8** buffer                   );
#endif  // !PNG

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // PETRA_IMAGES