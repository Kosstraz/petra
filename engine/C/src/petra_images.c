#define IMAGES_ALL
#include "../petra_images.h"







    /*////////*/
    //   BMP  //
    /*////////*/







    // Lecture du header
int8 bmp_header(const char* file_name, img_infos* infos, FILE* file)
{
        // lecture
    BMP_header header;
    int8 check = fread(&header, sizeof(BMP_header), 1, file);
    if (check < 0 || header.signature[0] != 'B' || header.signature[1] != 'M')
        return (error_fclose(file, BAD_FILE_FORMAT));

    if (header.compression != 0)
        return BMP_BAD_COMPRESSION;

        // attribution des infos
    infos->fileSize      = header.fileSize;
    infos->width         = header.width;
    infos->height        = header.height;
    infos->bitsPerPixel  = header.bitsPerPixel;
    infos->compression   = header.compression;
    infos->imageSize     = header.imageSize;
    if (infos->bitsPerPixel == 32)
        infos->CHANNEL_COLOR = BGRA_COLOR;
    else if (infos->bitsPerPixel == 24)
        infos->CHANNEL_COLOR = BGR_COLOR;

    return (0);
}

int8 bmp_datas(const char* file_name, uint8** buffer, img_infos* infos, FILE* file)
{
    int8 check = 0;

        // lecture
    uint8* datas = (uint8*)malloc(infos->imageSize * sizeof(uint8));
    if (datas == ((uint8*)0))
        return (error_fclose(file, BMP_ERROR));
    
    check = fread(datas, infos->imageSize, 1, file);
    if (check < 0)
    {
        free(datas);
        return (error_fclose(file, BMP_ERROR));
    }
        // attribution
    *buffer = datas;

    return (0);
}

    // Chargement entier de l'image
img_infos bmp_load(const char* file_name, uint8** buffer)
{
    img_infos infos;
    init_img_infos(&infos);

        // ouverture du fichier
    FILE* file = fopen(file_name, "rb");
    if (file == (FILE*)0)
        return (error_infos(infos, BMP_ERROR));

        // header .BMP
    infos.errorCode = bmp_header(file_name, &infos, file);
    if (infos.errorCode < 0)
        return (infos);

        // données du .BMP
    infos.errorCode = bmp_datas(file_name, buffer, &infos, file);
    if (infos.errorCode < 0)
        return (infos);

    fclose(file);
    return (infos);
}





    /*////////*/
    //   PNG  //
    /*////////*/






int8    png_pass_CRC_end_chunk(FILE* file)
{
    if (fseek(file, 4, SEEK_CUR) == -1)
        return NOT_SEEK;
    return(0);
}

int8    skip_png_chunk_datas(FILE* file, unsigned int byte_to_skip)
{
    if (fseek(file, byte_to_skip, SEEK_CUR) == -1 || png_pass_CRC_end_chunk(file) < 0)
        return NOT_SEEK;
    return (0);
}

int8    check_png_format(FILE* file)
{
    char signature[8];
    fread(signature, 8, 1, file);

    if (signature[1] != 'P' || signature[2] != 'N' || signature[3] != 'G')
        return BAD_FILE_FORMAT;
    printf("signature : %s\n", signature);
    return (0);
}

int8    ihdr_header_datas(FILE* file, img_infos* infos)
{
    PNG_IHDR header;
    fread(&header, sizeof(PNG_IHDR), 1, file);
    if (header.compression != 0 || header.interlace_method != 0)
        return (error_fclose(file, PNG_BAD_COMPRESSION));

    infos->width            =   inv_bin32(header.width);
    infos->height           =   inv_bin32(header.height);
    infos->bitsPerPixel     =   header.bitsPerPixel;
    infos->compression      =   header.compression;

    if (png_pass_CRC_end_chunk(file) < 0)
        return NOT_SEEK;

    return (0);
}

int8    png_headers(img_infos* infos, FILE* file, uint8* i)
{
        // début de la fonction récursive
    if (i == (uint8*)0)
    {
        i  = (uint8*)malloc(1);
       *i = 0;
    }
    else    (*i)++;

        // ouverture & vérification du format .PNG
    if (*i == 0 && check_png_format(file) < 0)
    {
        printf("bad png format\n");
        free(i);
        return (error_fclose(file, BAD_FILE_FORMAT));
    }

        // Taille des données
    uint32 dataLength;
    fread(&dataLength, sizeof(uint32), 1, file);
    uint32 inv_dataLength = inv_bin32(dataLength);

        // La section dans la quelle se trouve les données
    char header_type[4];
    fread(header_type, 4, 1, file);

        // IHDR header type (car c'est toujours le premier chunk des fichiers .PNG)
    if (*i == 0)
    {
        int8 check;
        if ((check = ihdr_header_datas(file, infos)) < 0)
            return (check);
        return (png_headers(infos, file, i));
    }

        // aller jusqu'aux données du fichier .PNG
    if (strcmp(header_type, "IDAT") != 0)
    {
        if (skip_png_chunk_datas(file, inv_dataLength) < 0)
            return NOT_SEEK;
        return (png_headers(infos, file, i));
    }
    else if (strcmp(header_type, "IDAT") == 0)
        infos->imageSize = inv_dataLength;
    
    free(i);
    return (0);
}

int8    png_datas(img_infos* infos, FILE* file, uint8** buffer)
{
    if (infos->imageSize <= 0)
        return PNG_ERROR;

    *buffer = (uint8*)malloc(infos->imageSize);
    fread(*buffer, infos->imageSize * sizeof(uint8), 1, file);

    fclose(file);
    return (0);
}

img_infos   png_load(const char* file_name, uint8** buffer)
{
    img_infos info;
    init_img_infos(&info);

        // ouverture
    FILE* file = fopen(file_name, "rb");
    if (file == (FILE*)0)
        return (error_infos(info, PNG_ERROR));

        // passer tous les headers hormis IHDR
    info.errorCode = png_headers(&info, file, (uint8*)0);
    if (info.errorCode < 0)
        return (info);

        // récupérer les données de l'image
    info.errorCode = png_datas(&info, file, buffer);
    *buffer = decompresse_deflate(*buffer, 604);    // !604 à modifier sûrement en info.imageSize
    if (*buffer == (uint8*)0)
        printf("BUFFER DECOMPRESSION ====== 0\n");

    return (info);
}




    /*//////////////*/
    //  FONDAMENTAL //
    /*//////////////*/




uint8*     decompresse_deflate(uint8* datas, uint32 bytes_count)
{
    uint32 uncompressed_size = 2 * bytes_count;
    uint8* uncompressed_datas = (uint8*)malloc(uncompressed_size);

    z_stream zstream;
    memset(&zstream, 0, sizeof(z_stream));

    if (inflateInit(&zstream) != Z_OK)
    {
        free(uncompressed_datas);
        return (uint8*)0; // DECOMPRESSION_FILE_ERR
    }

    zstream.next_in   = (Bytef*)        datas;
    zstream.avail_in  = (unsigned int)  bytes_count;
    zstream.next_out  = (Bytef*)        uncompressed_datas;
    zstream.avail_out = (unsigned int)  uncompressed_size;

    int result = inflate(&zstream, Z_NO_FLUSH);

    if (result == Z_OK || result == Z_STREAM_END)
    {
        //size_t real_uncompressed_size = uncompressed_size - stream.avail_out;
        return (uncompressed_datas);
    }

    free(uncompressed_datas);
    return (uint8*)0;
}





char*   find_img_extension_file(const char* file_name)        // ! Check when to free 'file_extension' after malloc()
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

    return (file_extension);
}

img_infos   img_load(const char* file_name, uint8** datas)
{
    char* file_extension = find_img_extension_file(file_name);

        // check extension name to load the good image
    if (strcmp(file_extension, "bmp") == 0 || strcmp(file_extension, "BMP") == 0)           //! BMP
    {
        free(file_extension);
        return (bmp_load(file_name, datas));
    }
    else if (strcmp(file_extension, "png") == 0 || strcmp(file_extension, "PNG") == 0)      //! PNG
    {
        free(file_extension);
        return (png_load(file_name, datas));
    }

        // retourne une erreur
    free(file_extension);

    img_infos infos;
    init_img_infos(&infos);
    infos.errorCode = NOT_IMG_FILE_SUPPORTED;
    return (infos);
}

void    img_free(uint8* datas)
{
    free(datas);
}

    // Initialisation de la structure des infos de l'image
void    init_img_infos(img_infos* infos)
{
    infos->errorCode     = 0;
    infos->datasOffset   = 0;
    infos->fileSize      = 0;
    infos->width         = 0;
    infos->height        = 0;
    infos->bitsPerPixel  = 0;
    infos->compression   = 0;
    infos->imageSize     = 0;
    infos->CHANNEL_COLOR = NO_CHANNEL;
}

    // fclose(file) + return(errorCode)
int         error_fclose(FILE* file, int errorCode)
{
    fclose(file);
    return (errorCode);
}

    // infos.errorCode = errorCode; 
    // return (infos);
img_infos   error_infos(img_infos& infos, int8 errorCode)
{
    infos.errorCode = errorCode;
    return (infos);
}