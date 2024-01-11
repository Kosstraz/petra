#include "../FileManager.h"

int WriteInFile(const char* fileName, char* text, unsigned long size)
{
        // Initialisation des variables
    if (size == 0)
        size      = strlen(text);
    FILE* file    = nullptrF;
        
        // Ouverture du fichier
    file      = fopen(fileName, WRITE);
    if (file == nullptrF)
    {
        fclose(file);
        return FILE_NULL;
    }

        // Ecriture dans le fichier
    unsigned int i = 0;
    while (i < size)
    {
        int putc_ok = fputc(text[i], file);
        if (putc_ok == (-1))
            return PUTC_NOT_OK;
        i++;
    }

        // Fermeture du fichier
    int close_log = fclose(file);
    if (close_log == (-1))
        return NOT_CLOSED;

    return (0);
}

int __read(const char* fileName, char** buffer, const char* reader_option, unsigned long FILE_SIZE_O)
{
        // Initialisation de variables
    if (FILE_SIZE_O == 0)
        FILE_SIZE_O = DEFAULT_FILE_SIZE;

    *buffer       = nullptrc;
    FILE* file    = nullptrF;
        
        // Ouverture du fichier
    file      = fopen(fileName, reader_option);
    if (file == nullptrF)
    {
        free(buffer);
        fclose(file);
        return FILE_NULL;
    }

        // Lecture du fichier
    unsigned int size =  0;
    int c         =  0;
    *buffer       =  (char*)malloc((FILE_SIZE_O + 1));

    while ((c = fgetc(file)) != EOF && size < FILE_SIZE_O - 1)
        (*buffer)[size++] = (char)c;

    (*buffer)[size] = '\0';

        // Fermeture du fichier
    int close_log = fclose(file);
    if (close_log == -1)
    {
        free(buffer);
        return NOT_CLOSED;
    }

    return (0);
}

int __read_at(const char* fileName, char** buffer, unsigned long at_index, const char* reader_option, unsigned long FILE_SIZE_O)
{
        // Initialisation des variables
    if (FILE_SIZE_O == 0)
        FILE_SIZE_O = DEFAULT_FILE_SIZE;

    *buffer       = nullptrc;
    FILE* file    = nullptrF;
        
        // Ouverture du fichier
    file      = fopen(fileName, reader_option);
    if (file == nullptrF)
    {
        free(buffer);
        fclose(file);
        return FILE_NULL;
    }

        // At
    int seek = fseek(file, at_index, SEEK_SET);
    if (seek != 0)
    {
        free(buffer);
        fclose(file);
        return NOT_SEEK;
    }

        // Lecture du fichier
    unsigned int size = 0;
    int c         = 0;
    *buffer       = (char*)malloc((FILE_SIZE_O + 1));

    while ((c = fgetc(file)) != EOF && size < FILE_SIZE_O - 1)
        (*buffer)[size++] = (char)c;

    (*buffer)[size] = '\0';

        // Fermeture du fichier
    int close_log = fclose(file);
    if (close_log == -1)
    {
        free(buffer);
        return NOT_CLOSED;
    }

    return (0);
}

int ReadFile(const char* fileName, char** buffer, unsigned long FILE_SIZE_O)
{   return (__read(fileName, buffer, READ, FILE_SIZE_O));          }

int ReadBinary(const char* fileName, char** buffer, unsigned long FILE_SIZE_O)
{   return (__read(fileName, buffer, READ_BINARY, FILE_SIZE_O));   }

int ReadFile_at(const char* fileName, char** buffer, unsigned long at_index, unsigned long FILE_SIZE_O)
{   return (__read_at(fileName, buffer, at_index, READ, FILE_SIZE_O));         }

int ReadBinary_at(const char* fileName, char** buffer, unsigned long at_index, unsigned long FILE_SIZE_O)
{   return (__read_at(fileName, buffer, at_index, READ_BINARY, FILE_SIZE_O));  }