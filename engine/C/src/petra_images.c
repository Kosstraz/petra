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
    if (check < 0 || header.signature[0] != 'B' || header.signature[1] != 'M')
    {
        fclose(file);
        return BAD_FILE_FORMAT;
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
    if (check < 0)
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





    /*////////*/
    //   PNG  //
    /*////////*/



int8        png_header  (const char* file_name,                  img_infos* infos)
{
        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == ((FILE*)0))
        return FILE_NULL;

        // lecture
    PNG_header header;
    int8 check = fread(&header, sizeof(PNG_header), 1, file);
    if (check == -1 || header.signature[1] != 'P' || header.signature[2] != 'N' || header.signature[3] != 'G')
    {
        fclose(file);
        return BAD_FILE_FORMAT;
    }

    if (header.compression != 0)
    {
        fclose(file);
        return PNG_BAD_COMPRESSION;
    }

    infos->width        = inv_bin32(header.width);
    infos->height       = inv_bin32(header.height);
    infos->bitsPerPixel =           header.bitDepth;   // Inversion des bits non nécessaire sur 1 octet
    infos->compression  =           header.compression;

    fclose(file);
    return (0);
}

int8        png_datas   (const char* file_name, uint8** buffer,  img_infos* infos)
{
        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == ((FILE*)0))
        return FILE_NULL;

        // seek
    if (fseek(file, sizeof(PNG_header), SEEK_SET) == -1)
    {
        fclose(file);
        return NOT_SEEK;
    }

        // lecture de la taille des données
    uint32 dataSize;
    if (fread(&dataSize, sizeof(uint32), 1, file) == (size_t)-1)
    {
        fclose(file);
        return PNG_ERROR;
    }
    uint32 inv_dataSize = inv_bin32(dataSize);

        // seek
    if (fseek(file, 4, SEEK_CUR) == -1)
    {
        fclose(file);
        return NOT_SEEK;
    }

    *buffer = (uint8*)malloc(inv_dataSize);
    int check = fread(*buffer, inv_dataSize, 1, file);
    if (check == -1)
    {
        free(*buffer);
        fclose(file);
        return PNG_ERROR;
    }

    fclose(file);
    return (0);
}

img_infos   png_load    (const char* file_name, uint8** buffer                   )
{
    img_infos info;
    init_img_infos(&info);

    info.errorCode = png_header(file_name, &info);
    if (info.errorCode < 0)
        return (info);

    info.errorCode = png_datas(file_name, buffer, &info);

    return (info);
}




    /*//////////////*/
    //  FONDAMENTAL //
    /*//////////////*/



img_infos img_load(const char* file_name, uint8** datas)
{
        // count of char
    const long file_name_size = strlen(file_name);
    char* file_extension;

        // extension name length & malloc
    uint8 extension_size = 0;
    if (file_name[file_name_size - 4] == '.')
        extension_size = 3;
    else
        extension_size = 4;
    file_extension = (char*)malloc(extension_size + 1);

        // extension name copy
    uint8 i = file_name_size - extension_size;
    uint8 j = 0;
    while (i < file_name_size)
        file_extension[j++] = file_name[i++];
    file_extension[j] = '\0';


        // check extension name to load the good image
    if (strcmp(file_extension, "bmp") == 0)
    {
        free(file_extension);
        return (bmp_load(file_name, datas));
    }
    else if (strcmp(file_extension, "png") == 0)
    {
        free(file_extension);
        return (png_load(file_name, datas));
    }

        // retourne une erreur
    img_infos infos;
    init_img_infos(&infos);
    infos.errorCode = NOT_IMG_FILE_SUPPORTED;
    return (infos);
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