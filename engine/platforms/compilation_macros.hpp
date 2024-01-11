#pragma once

// L'utilisation de __fastcall se fait lorsque nous voulons passer la mémoire dans les registres du CPU plutôt que dans la pile
// Cela peut s'avérer très utile pour la rapidité de compilation du code si, et seulement si, il n'y pas trop de paramètres et que ceux-ci ne sont pas des objets trop complexes
// Peut vouloir dire que les deux premiers paramètres seront stockés dans les registres tandis que les autres dans la pile
#define REG     __fastcall

// L'utilisation de __vectorcall peut s'avérer extrêmement utile si la dite fonction procède à des calculs lourds sur des objects vectoriels ou matriciels, la plupart du temps
#define MATH    __vectorcall

// Appel conventionnel et classique des fonctions, utilise la pile et supprime la mémoire après exécution de la fonction
#define WINAPI  __stdcall

#define THIS    __thiscall

// Une autre convention utilisée sur certaines plateformes, principalement pour les appels de fonctions entre des modules compilés avec des compilateurs différents.
// Les paramètres sont généralement passés sur la pile, et c'est la responsabilité de l'appelant de nettoyer la pile.
#define MANUAL  __cdecl

// Exécution d'un code assembleur
#define DEL_FtMem(byteToDelete) asm("subl %0, %%esp" : : "g" (byteToDelete))

#define s_CAST(type, varName) static_cast<type>(varName)