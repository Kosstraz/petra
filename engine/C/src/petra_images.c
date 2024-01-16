#define IMAGES_ALL
#include "../petra_images.h"

    /*////////*/
    //   BMP  //
    /*////////*/

    // Lecture du header
int8 bmp_header(const char* file_name, img_infos* infos)
{
        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == ((FILE*)0))
        return FILE_NULL;

        // lecture
    BMP_header header;
    int8 check = fread(&header, sizeof(BMP_header), 1, file);
    if ((unsigned long long)check < sizeof(BMP_header) || header.signature[0] != 'B' || header.signature[1] != 'M')
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

    // Lecture des pixels
int8 bmp_datas(const char* file_name, uint8** buffer, img_infos* infos)
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
    uint8* datas = (uint8*)malloc(infos->imageSize * sizeof(uint8));
    if (datas == ((uint8*)0))
    {
        fclose(file);
        return BMP_ERROR;
    }
    check = fread(datas, infos->imageSize, 1, file);
    if ((uint32)check < infos->imageSize)
    {
        fclose(file);
        free(datas);
        return BMP_ERROR;
    }

        // attribution
    *buffer = datas;

        // fermeture
    check = fclose(file);
    if (check == -1)
        return NOT_CLOSED;

    return (0);
}

    // Chargement entier de l'image
img_infos bmp_load(const char* file_name, uint8** buffer)
{
    img_infos infos;
    init_img_infos(&infos);

    infos.errorCode = bmp_header(file_name, &infos);
    if (infos.errorCode < 0)
        return infos;

    infos.errorCode = bmp_datas(file_name, buffer, &infos);
    if (infos.errorCode < 0)
        return infos;

    return infos;
}

    // Initialisation de la structure des infos de l'image
void init_img_infos(img_infos* infos)
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





    /*////////*/
    //   PNG  //
    /*////////*/






