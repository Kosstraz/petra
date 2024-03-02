#include <base/PetraO.hpp>

#include <utils/f_utils.h>

    // Un pointeur sur une liste
    // Le nom des objets sera : strjoin(common_name, itoa(count))
template <class PetraObjectType>
PetraObjectType** PetraO::Creates(const char* common_name, uint64 count)   noexcept
{
    PetraObjectType** ret = nullptr;
    ret = new PetraObjectType*[count];
    for (uint64 i = 0; i < count; i++)
    {
        char* int_ascii = itoa(i);
        char* join = strjoin(common_name, int_ascii, 0, 0);
        ret[i] = new PetraObjectType(static_cast<const char*>(join));
        free(int_ascii);
        //free(join);           // ! développe une erreur, à ne pas supprimer car c'est le nom pointeur de l'objet
    }
    return (ret);
}