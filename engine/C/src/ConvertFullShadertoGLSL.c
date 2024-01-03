#include "../ConvertFullShadertoGLSL.h"

void ConvertShaderExtension_GLSL(const char* VFS_fileName, unsigned int MAX_FILE_SIZE)
{
    /// Initialisation des variables
    unsigned int VFS_fileNameSize = 0;
    char* frag_temp = nullptrc;
    char* vert_temp = nullptrc;
    char* glsl_temp = nullptrc;
        
    char* frag_fileName = nullptrc;
    char* vert_fileName = nullptrc;

    char*  VFS_content  = nullptrc;
    char*  frag_content = nullptrc;
    char*  vert_content = nullptrc;

        // Lecture du fichier
    ReadFile(VFS_fileName, &VFS_content, MAX_FILE_SIZE);

    /// Parçage
    _parcingVFS(VFS_content, &frag_content, "FRAGMENT_SOURCE", MAX_FILE_SIZE);
    _parcingVFS(VFS_content, &vert_content, "VERTEX_SOURCE"  , MAX_FILE_SIZE);

    /// Création du nom des nouveaux fichiers
        //Pour GLSL
    VFS_fileNameSize = strlen(VFS_fileName);
    glsl_temp    = (char*)malloc(5 * sizeof(char));
    glsl_temp[0] = 'g'; glsl_temp[1] = 'l'; glsl_temp[2] = 's'; glsl_temp[3] = 'l'; glsl_temp[4] = '\0';

        //Pour FRAG
    frag_fileName = (char*) malloc(VFS_fileNameSize + 1);
    strcpy(frag_fileName, VFS_fileName);
    frag_temp     = (char*)    malloc(5 * sizeof(char));
    frag_temp[0] = 'f'; frag_temp[1] = 'r'; frag_temp[2] = 'a'; frag_temp[3] = 'g'; frag_temp[4] = '.';

    for (unsigned char i = VFS_fileNameSize - 8; i < VFS_fileNameSize - 2; i++)
        frag_fileName[i] = frag_temp[i - (VFS_fileNameSize - 8)];

    for (unsigned char i = VFS_fileNameSize - 3; i < VFS_fileNameSize + 2; i++)
        frag_fileName[i] = glsl_temp[i - (VFS_fileNameSize - 3)];

        //Pour VERT
    vert_fileName = (char*) malloc(VFS_fileNameSize + 1);
    strcpy(vert_fileName, VFS_fileName);
    vert_temp     = (char*)    malloc(5 * sizeof(char));
    vert_temp[0] = 'v'; vert_temp[1] = 'e'; vert_temp[2] = 'r'; vert_temp[3] = 't'; vert_temp[4] = '.';

    for (unsigned char i = VFS_fileNameSize - 8; i < VFS_fileNameSize - 2; i++)
        vert_fileName[i] = vert_temp[i - (VFS_fileNameSize - 8)];

    for (unsigned char i = VFS_fileNameSize - 3; i < VFS_fileNameSize + 2; i++)
        vert_fileName[i] = glsl_temp[i - (VFS_fileNameSize - 3)];

    /// Création des fichiers et écriture
    WriteInFile(frag_fileName, frag_content, 0);
    WriteInFile(vert_fileName, vert_content, 0);

    /// Désallocation de la mémoire
    free(frag_temp);
    free(vert_temp);
    free(glsl_temp);

    free(frag_fileName);
    free(vert_fileName);

    free(VFS_content) ;
    free(frag_content);
    free(vert_content);
}



void _parcingVFS(const char* VFS_content, char** new_content, const char* BEGIN_KEYWORD, unsigned int MAX_FILE_SIZE)
{
    /// Initialisation des variables
    unsigned int i      = 0;
    unsigned int beginc = 0;

    if (MAX_FILE_SIZE == 0)
        MAX_FILE_SIZE = DEFAULT_FILE_SIZE;

    (*new_content) = (char*) malloc(MAX_FILE_SIZE + 1);

    /// Parçage
        // Trouver le 1er caractère
    while (VFS_content[i] != '[')
        i++;

        // Assimilé à FRAG ou VERT
    while (!(VFS_content[  i  ] == BEGIN_KEYWORD[0] && VFS_content[i + 1] == BEGIN_KEYWORD[1] && VFS_content[i + 2] == BEGIN_KEYWORD[2] && VFS_content[i + 3] == BEGIN_KEYWORD[3]))
        i++;
    
    while (VFS_content[i] != '{')
        i++;

    i++;
    beginc = (++i);

        //Recherche du mot-clef
    if (BEGIN_KEYWORD[0] == 'V')
    {
        while (VFS_content[i] != '\0')
        {
            (*new_content)[i - beginc] = VFS_content[i];
            i++;
        }
    }
    else if (BEGIN_KEYWORD[0] == 'F')
    {
        while (VFS_content[i] != '[')
        {
            (*new_content)[i - beginc] = VFS_content[i];
            i++;
        }
    }

        // Vérification des limites à atteindre pour une définition complète
    if (VFS_content[i] == '\0' || VFS_content[i] == '[')
    {
        while (VFS_content[i] == '\0' && VFS_content[i] == '[')
        {
            (*new_content)[i - beginc] = ' ';
            i--;
        }
        i--;
    }

    if (VFS_content[i] != '\0' || VFS_content[i] != '[')
    {
        while (VFS_content[i] != '}')
        {
            (*new_content)[i - beginc] = ' ';
            i--;
        }
        i--;
        (*new_content)[i - beginc] = '\0';
    }
}