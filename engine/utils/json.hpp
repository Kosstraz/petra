#ifndef PETRA_JSONREADER_H
#define PETRA_JSONREADER_H

#include <unordered_map>
#include <stdio.h>

#include <utils/f_utils.h>

typedef std::unordered_multimap<char*, char*> ArrayForJSON;

    // Met dans un 'char* buffer' les données du JSON
    // Si aucune erreur renvoie la 'size' du buffer, sinon return('size' < 0)
int buffering_json(const char* file_name, char** buffer);

    // Détecte rapidement si le fichier à la ponctuation d'un JSON
int detect_json(const char* buffer, const long buffer_size, long* i);

int parse_key(const char* buffer, char** key, long* i);

int parse_value(const char* buffer, char** val, long* i);

    // Vérifie si après cette clef il y a une autre clef
void check_other_key(const char* buffer, long* i);

    // Ouverture et recherche des éléments clefs
int json_open(const char* file_name, ArrayForJSON*  multimap);

#endif