#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define  nullptrF       ((FILE*)0x0)
#define  nullptrc       ((char*)0x0)

#define  READ           ("r" )
#define  READ_BINARY    ("rb")
#define  WRITE          ("w" )
#define  READ_WRITE     ("r+")

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <platforms/errors_macros.hpp>
#include <platforms/speed_macros.hpp>

    // (si size = 0) = strlen(text) + 1
    // Renvoie une chaîne de caractères avec le contenu du fichier en question  
int WriteInFile(const char* fileName, char* text, unsigned long size);

int __read(const char* fileName, char*& buffer, unsigned char reader_option, unsigned long FILE_SIZE_O);

int __read_at(const char* fileName, char*& buffer, unsigned long at_index, unsigned char reader_option, unsigned long FILE_SIZE_O);

    // (si FILE_SIZE_O = 0) = DEFAULT_FILE_SIZE (2048 octets)
    // Renvoie une chaîne de caractères avec le contenu du fichier en question
int ReadFile(const char* fileName, char*& buffer, unsigned long FILE_SIZE_O);

    // (si FILE_SIZE_O = 0) = DEFAULT_FILE_SIZE (2048 octets)
    // Renvoie une chaîne de caractères avec le contenu binaire du fichier en question (utile pour des fichiers encodés en hexadécimal)
int ReadBinary(const char* fileName, char*& buffer, unsigned long FILE_SIZE_O);


    // (si FILE_SIZE_O = 0) = DEFAULT_FILE_SIZE (2048 octets)
    // Renvoie une chaîne de caractères avec le contenu du fichier en question
    // Commence la lecture à la position 'at_index'
int ReadFile_at(const char* fileName, char*& buffer, unsigned long at_index, unsigned long FILE_SIZE_O);

    // (si FILE_SIZE_O = 0) = DEFAULT_FILE_SIZE (2048 octets)
    // Renvoie une chaîne de caractères avec le contenu binaire du fichier en question (utile pour des fichiers encodés en hexadécimal)
    // Commence la lecture à la position 'at_index'
int ReadBinary_at(const char* fileName, char*& buffer, unsigned long at_index, unsigned long FILE_SIZE_O);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif