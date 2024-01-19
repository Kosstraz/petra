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

char* strjoin(const char* str1, const char* str2, long size1, long size2)
{
    if (size1 == 0)
        size1 = strlen(str1);
    if (size2 == 0)
        size2 = strlen(str2);

    long total_size = size1 + size2;
    char* ret = (char*)malloc(total_size + 1);

    long i = -1;
    while (++i < total_size + 1)
        ret[i] = (i < size1) ? str1[i] : str2[i - size1];
    ret[total_size] = '\0';
    
    return (ret);
}
