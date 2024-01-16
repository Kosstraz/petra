#include "../f_utils.h"

int fsimc(const char* v, const char c, long* i)
{
    int temp = *i;

    while (v[temp] != c && v[temp] != '\0')
        temp++;

    if (v[temp] == c)
    {
        *i = ++temp;
        return (0);
    }

    return (-1);
}

int fnextc(const char* v, const char c, long* i)
{
    int temp = *i;

    while (v[temp] != c && (v[temp] == ' ' || v[temp] == '\n'))
        temp++;

    if (v[temp] != c && v[temp] != ' ')
        return (-1);

    *i = ++temp;    // <-- 'i' s'arrête 1 cran juste après le caractère 'c' trouvé.
    return (0);
}

int fprevc(const char* v, const char c, const long file_size)
{
    int temp = file_size;

    while (v[temp] != c && (v[temp] == ' ' || v[temp] == '\0' || v[temp] == '\n'))
        temp--;

    if (v[temp] != c && v[temp] != ' ')
        return (-1);

    return (0);
}

int to_nextc(const char* v, const char c, long* i, char** buffer)
{
    long temp = (*i - 1);
    long size = 0;

    while (v[temp + 1] != c)
    {
        size++;
        temp++;
    }

    *buffer = (char*)malloc((size + 1));
    if (*buffer == ((char*)0))
        return (-1);

    long j = 0;
    temp = *i;
    while (j < size)
        (*buffer)[j++] = v[temp++];
    (*buffer)[size] = '\0';

    *i = ++temp;    // <-- 'i' s'arrête 1 cran juste après le caractère 'c' trouvé.
    return (0);
}