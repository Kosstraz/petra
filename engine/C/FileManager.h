#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#define  nullptrF           ((FILE*)0)
#define  nullptrc           ((char*)0)

#define  DEFAULT_FILE_SIZE  MEDIUM_FILE_SIZE
#define  COMPLX_FILE_SIZE   (102400U )
#define  TITAN_FILE_SIZE    (15096U  )
#define  LARGE_FILE_SIZE    (5096U   )
#define  MEDIUM_FILE_SIZE   (2048U   )
#define  SHORT_FILE_SIZE    (1024U   )
#define  MINI_FILE_SIZE     (512U    )

#define READ        ("r" )
#define WRITE       ("w" )
#define READ_WRITE  ("r+")

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

    // (si MAX_FILE_SIZE = 0) = DEFAULT_FILE_SIZE (2048)
    // Renvoie une chaîne de caractères avec le contenu du fichier en question
void ReadFile(const char* fileName, char** content, unsigned int MAX_FILE_SIZE);

    // (si size = 0) = strlen(text) + 1
    // Renvoie une chaîne de caractères avec le contenu du fichier en question  
void WriteInFile(const char* fileName, char* text, unsigned int size);

#endif