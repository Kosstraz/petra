#include "../petra_images.h"

    /*////////*/
    //   BMP  //
    /*////////*/

int8 bmp_header(const char* file_name, BMP_infos* infos)
{
        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == ((FILE*)0))
        return FILE_NULL;

        // lecture
    BMP_header header;
    int8 check = fread(&header, sizeof(BMP_header), 1, file);
    if (check == -1 || header.signature[0] != 'B' || header.signature[1] != 'M')
    {
        fclose(file);
        return BMP_ERROR;
    }

    if (header.compression != 0)
        return BMP_BAD_COMPRESSION;


        // attribution des infos
    infos->fileSize      = header.fileSize;
    infos->width         = header.width;
    infos->height        = header.height;
    infos->bitsPerPixel  = header.bitsPerPixel;
    infos->compression   = header.compression;
    infos->imageSize     = header.imageSize;

        // fermeture
    check = fclose(file);
    if (check == -1)
        return NOT_CLOSED;

    return (0);
}

int8 bmp_datas_24bits(const char* file_name, unsigned char** buffer, BMP_infos* infos)
{
        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == ((FILE*)0))
        return FILE_NULL;

        // déplacement du curseur
    int8 check = fseek(file, infos->datasOffset, SEEK_SET);
    if (check == -1)
    {
        fclose(file);
        return NOT_SEEK;
    }

        // lecture
    unsigned char* datas = (unsigned char*)malloc(infos->imageSize);
    check = fread(datas, infos->imageSize, 1, file);
    if (check == -1 || datas == ((unsigned char*)0))
    {
        fclose(file);
        free(datas);
        return BMP_ERROR;
    }

        // attribution
    *buffer = datas;

        // fermeture
    check = fclose(file);
    free(datas);
    if (check == -1)
        return NOT_CLOSED;

    return (0);
}

int8 bmp_datas_32bits(const char* file_name, unsigned char** buffer, BMP_infos* infos)
{
        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == ((FILE*)0))
        return FILE_NULL;

        // déplacement du curseur
    int8 check = fseek(file, infos->datasOffset, SEEK_SET);
    if (check == -1)
    {
        fclose(file);
        return NOT_SEEK;
    }

        // lecture
    //BMP_32bits_datas* datas = (BMP_32bits_datas*)malloc(infos->imageSize);
    unsigned char* datas = (unsigned char*)malloc(infos->imageSize * sizeof(unsigned char));
    check = fread(datas, infos->imageSize, 1, file);
    if (check == -1 || datas == ((unsigned char*)0))
    {
        fclose(file);
        free(datas);
        return BMP_ERROR;
    }
    printf("r: %d, g: %d, b: %d, a: %d\n", datas[475000], datas[475001], datas[475002], datas[475003]);

        // attribution
    *buffer = datas;

    //printf("r: %d, g: %d, b: %d, a: %d\n", buffer[0 + 475000], buffer[1 + 475000], buffer[2 + 475000], buffer[3 + 475000]);

        // fermeture
    check = fclose(file);
    //free(datas);
    if (check == -1)
        return NOT_CLOSED;

    return (0);
}

int8 bmp_datas(const char* file_name, unsigned char** buffer, BMP_infos* infos)
{
    if      (infos->bitsPerPixel == 32)
        return (bmp_datas_32bits(file_name, buffer, infos));
    else if (infos->bitsPerPixel == 24)
        return (bmp_datas_24bits(file_name, buffer, infos));
    else
        return (BMP_ERROR);
}

BMP_infos bmp_load(const char* file_name, unsigned char** buffer)
{
    BMP_infos infos;
    init_BMP_infos(&infos);

    infos.errorCode = bmp_header(file_name, &infos);
    if (infos.errorCode < 0)
        return infos;

    infos.errorCode = bmp_datas(file_name, buffer, &infos);
    if (infos.errorCode < 0)
        return infos;

    return infos;
}



void init_BMP_infos(BMP_infos* infos)
{
    infos->errorCode   = 0;
    infos->datasOffset = 0;
    infos->fileSize    = 0;
    infos->width       = 0;
    infos->height      = 0;
    infos->bitsPerPixel= 0;
    infos->compression = 0;
    infos->imageSize   = 0;
}