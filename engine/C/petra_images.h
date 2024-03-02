#ifndef PETRA_IMAGES_H
#define PETRA_IMAGES_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "../utils/f_hexa.h"

#include "../platforms/errors_macros.hpp"   // enlever ../
#include "../platforms/types_macros.hpp"    // enlever ../

#define IMAGES_ALL
#define IMAGES_BMP
#define IMAGES_PNG

#define NO_CHANNEL  0x0000
#define RGBA_COLOR  0x1908
#define RGB_COLOR   0x1907
#define BGR_COLOR   0x80E0
#define BGRA_COLOR  0x80E1

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
        uint16 CHANNEL_COLOR;

    }   img_infos;
#pragma pack(pop)

uint8*      decompresse_deflate     (uint8* datas, uint32 bytes_count); // décompresse DEFLATE

char*       find_img_extension_file (const char* file_name);
img_infos   img_load                (const char* file_name, uint8** datas);
void        img_free                (uint8* datas);
void        init_img_infos          (img_infos* infos);
int         error_fclose            (FILE* file, int errorCode);
img_infos   error_infos             (img_infos& infos, int8 errorCode);




    // Toutes les fonctions et structures liées aux fichiers images en général
#ifdef  IMAGES_ALL
    #define IMAGES_BMP
    #define IMAGES_PNG
#endif  // !ALL



    /*////////*/
    //   BMP  //
    /*////////*/



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
int8        bmp_header  (const char* file_name,                 img_infos* infos, FILE* file);
int8        bmp_datas   (const char* file_name, uint8** buffer, img_infos* infos, FILE* file);
img_infos   bmp_load    (const char* file_name, uint8** buffer                  );
#endif  // !BMP




    /*////////*/
    //   PNG  //
    /*////////*/



#ifdef  IMAGES_PNG
    #pragma pack(push, 1)
typedef struct PNG_IHDR {    // IHDR header -> 13 octets
    uint32 width;
    uint32 height;
    uint8  bitsPerPixel;
    uint8  colorType;
    uint8  compression;
    uint8  filter_method;
    uint8  interlace_method;

}   PNG_IHDR;
    #pragma pack(pop)
int8        skip_png_chunk_datas    (FILE* file, unsigned int byte_to_skip);
int8        png_pass_CRC_end_chunk  (FILE* file);
int8        check_png_format        (FILE* file);
int8        ihdr_header_datas       (FILE* file,            img_infos*  infos                 );
int8        png_headers             (FILE* file,            img_infos*  infos,  uint8*  i     );
int8        png_datas               (FILE* file,            img_infos*  infos,  uint8** buffer);
img_infos   png_load                (const char* file_name, uint8**     datas                 );
#endif  // !PNG








#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // PETRA_IMAGES