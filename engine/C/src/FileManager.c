#include "../FileManager.h"

void ReadFile(const char* fileName, char** ret, unsigned int MAX_FILE_SIZE)
{
        // Initialisation des variables
    if (MAX_FILE_SIZE == 0)
        MAX_FILE_SIZE = DEFAULT_FILE_SIZE;

    *ret              = nullptrc;
    FILE* file        = nullptrF;
        
        // Ouverture du fichier
    file      = fopen(fileName, READ);
    if (file == nullptrF)
    {
        fclose(file);
        return;
    }

        // Lecture du fichier
    unsigned int size = 0;
    int c    = 0;
    *ret     = (char*)malloc((MAX_FILE_SIZE + 1));

    while ((c = fgetc(file)) != EOF && size < MAX_FILE_SIZE - 1)
        (*ret)[size++] = (char)c;

    (*ret)[size] = '\0';

        // Fermeture du fichier
    int close_log = fclose(file);
    if (close_log == -1)
        return;
}



void WriteInFile(const char* fileName, char* text, unsigned int size)
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
        return;
    }

        // Ecriture dans le fichier
    unsigned int i = 0;
    while (i < size)
    {   
        fputc(text[i], file);
        i++;
    }

        // Fermeture du fichier
    int close_log = fclose(file);
    if (close_log == -1)
        return;
}