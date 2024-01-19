#ifndef F_UTILS_H
#define F_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

    // Cherche le caractère 'c'suivant dans 'v'.
    // Si la valeur que renvoie la fonction est inférieur à 0 alors -> erreur
    // !!! 'i' s'arrête 1 cran juste après le caractère 'c' trouvé !!!
int fsimc(const char* v, const char c, long* i);

    // Vérifie si le prochain caractère non-vide est 'c'
    // Si la valeur que renvoie la fonction est inférieur à 0 alors -> erreur
    // !!! 'i' s'arrête 1 cran juste après le caractère 'c' trouvé !!!
int fnextc(const char* v, const char c, long* i);

    // Cherche le caractère 'c' non-vide précédent dans 'v'.
    // Si la valeur que renvoie la fonction est inférieur à 0 alors -> erreur
int fprevc(const char* v, const char c, const long file_size);

    // Cherche le caractère non-vide suivant et enregistre dans 'buffer' tous les caractères entre '*i' et le caractère 'c'
    // Si la valeur que renvoie la fonction est égale au paramètre 'i' inséré, alors le prochain caractère n'est pas celui demandé
int to_nextc(const char* v, const char c, long* i, char** buffer);

    // Fusionne deux chaînes de caractères en allouant la bonne taille de mémoire
    // si (size1 = 0 || size2 = 0)  =>  (size1 = strlen(str1) && size2 = strlen(str2))
char* strjoin(const char* str1, const char* str2, long size1, long size2);

#ifdef __cplusplus
}
#endif

#endif