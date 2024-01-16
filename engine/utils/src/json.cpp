#include <utils/json.hpp>

#include <cstring>

int buffering_json(const char* file_name, char** buffer)
{
    int log = 0;

        // Ouverture
    FILE* file = fopen(file_name, "r");
    if (file == (FILE*)0)
        return JSON_BAD_OPENNING;

        // Récupérer la taille du fichier
    log = fseek(file, 0, SEEK_END);
    const long fileSize(ftell(file));
    rewind(file);

    if (log == (-1))
        return JSON_BAD_SEEKING;

        // Prise des données
    int c(0);
    long size(0);
    
    *buffer = (char*)malloc((fileSize + 1) * sizeof(char));
    if (*buffer == nullptr)
    {
        fclose(file);
        return FILE_NULL;
    }
    while ((c = fgetc(file)) != EOF && size < fileSize)
        (*buffer)[size++] = c;
    (*buffer)[size] = '\0';

        // Fermeture
    log = fclose(file);
    if (log == (-1))
    {
        free(*buffer);
        return JSON_NOT_CLOSED;
    }

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
        return (-1);

    if (to_nextc(buffer, '"', &j, key) < 0)
        return (-2);

    if (fnextc(buffer, ':', &j) < 0)
        return (-3);

    if (fnextc(buffer, '[', &j) < 0)
        return (-4);

    *i = j;
    return (0);
}

int parse_value(const char* buffer, char** val, long* i)
{
    long j(*i);

    if (fnextc(buffer, '"', &j) < 0)
        return (-1);

    if (to_nextc(buffer, '"', &j, val) < 0)
        return (-2);

    *i = j;
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
    long size_log = buffering_json(file_name, &data);   // JSON_BAD_OPENNING || JSON_BAD_SEEKING || FILE_NULL || JSON_NOT_CLOSED
    if (size_log < 0)
        return (size_log);

    long i(0);
    if (detect_json(data, size_log, &i) < 0)
        return JSON_ERROR_FILE_FORMAT;

    char* keys;
    while (parse_key(data, &keys, &++i) == 0)
    {
        char* val;
        int log = 0;
        while ((log = parse_value(data, &val, &i)) == 0)
            multimap->insert(std::pair<const char*, const char*>(keys, val));

        check_other_key(data, &i);
    }

    free(data);
    return (0);
}