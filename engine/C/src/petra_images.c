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

int8 bmp_datas_24bits(const char* file_name, void** buffer, BMP_infos* infos)
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
    BMP_24bits_datas* datas = (BMP_24bits_datas*)malloc(infos->imageSize);
    check = fread(datas, infos->imageSize, 1, file);
    if (check == -1 || datas == ((BMP_24bits_datas*)0))
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

int8 bmp_datas_32bits(const char* file_name, void** buffer, BMP_infos* infos)
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
    BMP_32bits_datas* datas = (BMP_32bits_datas*)malloc(infos->imageSize);
    check = fread(datas, infos->imageSize, 1, file);
    if (check == -1 || datas == ((BMP_32bits_datas*)0))
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

int8 bmp_datas(const char* file_name, void** buffer, BMP_infos* infos)
{
    if      (infos->bitsPerPixel == 32)
        return (bmp_datas_32bits(file_name, buffer, infos));
    else if (infos->bitsPerPixel == 24)
        return (bmp_datas_24bits(file_name, buffer, infos));
    else
        return (BMP_ERROR);
}

BMP_infos bmp_load(const char* file_name, void** buffer)
{
    BMP_infos infos;
    init_BMP_infos(&infos);

    int8 check = bmp_header(file_name, &infos);
    if (check < 0)
    {
        infos.errorCode = check;
        return infos;
    }

    check = bmp_datas(file_name, buffer, &infos);
    if (check < 0)
    {
        infos.errorCode = check;
        return infos;
    }

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