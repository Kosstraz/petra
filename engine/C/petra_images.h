#ifndef PETRA_IMAGES_H
#define PETRA_IMAGES_H

#include <stdio.h>
#include <stdlib.h>

#include "platforms/errors_macros.hpp"
#include "platforms/types_macros.hpp"
#define IMAGES_ALL

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
    typedef struct BMP_infos {
        int8   errorCode;
        uint32 datasOffset;
        uint32 fileSize;
        int32  width;
        int32  height;
        uint16 bitsPerPixel;
        uint32 compression;
        uint32 imageSize;

    }   BMP_infos;
        // BGR methode
    typedef struct BMP_24bits_datas {
        int8 b;
        int8 g;
        int8 r;
    }   BMP_24bits_datas;
        // BGRA methode
    typedef struct BMP_32bits_datas {
        int8 b;
        int8 g;
        int8 r;
        int8 a;
    }   BMP_32bits_datas;
    #pragma pack(pop)

int8        bmp_header      (const char* file_name, BMP_infos* infos);
int8        bmp_datas_24bits(const char* file_name, void** buffer, BMP_infos* infos);
int8        bmp_datas_32bits(const char* file_name, void** buffer, BMP_infos* infos);
int8        bmp_datas       (const char* file_name, void** buffer, BMP_infos* infos);
BMP_infos   bmp_load        (const char* file_name, void** buffer);

void init_BMP_infos(BMP_infos* infos);
#endif  // !BMP




#ifdef  IMAGES_PNG
#endif  // !PNG

#endif  // PETRA_IMAGES