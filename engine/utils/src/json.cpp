#include <utils/json.hpp>

#define OPEN -1
#define SEEK -2

#define BUFFERING -5
#define DETECT_JSON -6

int buffering_json(const char* file_name, char** buffer)
{
    int log = 0;

        // Ouverture
    FILE* file = fopen(file_name, "r");
    if (file == (FILE*)0)
        return OPEN;

        // Récupérer la taille du fichier
    log = fseek(file, 0, SEEK_END);
    const long fileSize(ftell(file));
    rewind(file);

    if (log == (-1))
        return SEEK;

        // Prise des données
    int c(0);
    long size(0);
    
    *buffer = (char*)malloc((fileSize + 1) * sizeof(char));
    while ((c = fgetc(file)) != EOF && size < fileSize)
        (*buffer)[size++] = c;
    (*buffer)[size] = '\0';

        // Fermeture
    fclose(file);

    return (size);
}

int detect_json(const char* buffer, const long buffer_size, long* i)
{
    long j(0);
    if (fnextc(buffer, '{', &j) < 0 || fprevc(buffer, '}', buffer_size) < 0)
        return (-1);

    *i = j;
    return (0);
}

int parse_key(const char* buffer, char** key, long* i)
{
    long j(*i);

    if (fnextc(buffer, '"', &j) < 0)
        return -10;

    if (to_nextc(buffer, '"', &j, key) < 0)
        return -11;

    if (fnextc(buffer, ':', &j) < 0)
        return -12;

    if (fnextc(buffer, '[', &j) < 0)
        return -13;

    *i = j;
    return (0);
}

int parse_value(const char* buffer, char** val, long* i)
{

    if (fnextc(buffer, '"', i) < 0)
        return -10;

    if (to_nextc(buffer, '"', i, val) < 0)
        return -11;

    if (fnextc(buffer, ',', i) < 0)
        return (0);

    return (0);
}

void check_other_key(const char* buffer, long* i)
{
    fnextc(buffer, ']', i);
    fnextc(buffer, ',', i);
}

int json_open(const char* file_name, ArrayForJSON*  multimap)
{
    char* data;
    long size = buffering_json(file_name, &data);
    if (size < 0)
        return BUFFERING;

    long i(0);
    if (detect_json(data, size, &i) < 0)
        return DETECT_JSON;

    *multimap = ArrayForJSON();
    char* keys;
    while (parse_key(data, &keys, &++i) == 0)
    {
        char* val;
        while (parse_value(data, &val, &i) == 0)
            multimap->insert(std::pair<char*, char*>(keys, val));

        check_other_key(data, &i);
    }

    free(data);
    return (0);
}