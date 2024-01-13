#include "../Shader.hpp"

    /// CONSTRUCTEURS

Shader::Shader(const char* VFS_filename)
{
    this->programID  = 0;
    this->fragShader = ((char*)0);
    this->vertShader = ((char*)0);
    
    ConvertShaderExtension_GLSL(VFS_filename, PRINCIPAL_SHADER_SIZE);
    DEBUG(SHADER_LOG, "Fichier .vfs.glsl converti avec succes en .frag.glsl et en .vert.glsl.");

    delete VFS_filename;
}

Shader::Shader(const char* fragShader, const char* vertShader)
{
    this->programID  = 0;
    this->fragShader = ((char*)0);
    this->vertShader = ((char*)0);
    
    ReadFile(fragShader, &this->fragShader, PRINCIPAL_SHADER_SIZE);
    ReadFile(vertShader, &this->vertShader, PRINCIPAL_SHADER_SIZE);
    DEBUG(SHADER_LOG, "Fichier .glsl lu avec succes, avec une taille maximale de 5096 bits.");
    
    delete fragShader;
    delete vertShader;
}

Shader::Shader(const char* VFS_filename, const char* fragShader, const char* vertShader)
{
    this->programID  = 0;
    this->fragShader = ((char*)0);
    this->vertShader = ((char*)0);
    
    ConvertShaderExtension_GLSL(VFS_filename, PRINCIPAL_SHADER_SIZE);
    ReadFile(fragShader, &this->fragShader,   PRINCIPAL_SHADER_SIZE);
    ReadFile(vertShader, &this->vertShader,   PRINCIPAL_SHADER_SIZE);
    DEBUG(SHADER_LOG, "Fichier .glsl lu avec succes, avec une taille maximale de 5096 bits.");
}

Shader::~Shader()
{   this->Free();   }

    /// METHODES

const char* Shader::GetFragment() const noexcept
{   return this->fragShader;  }

const char* Shader::GetVertex() const noexcept
{   return this->vertShader;    }

void Shader::Set_frag(const char* frag_file_name) noexcept
{
    ReadFile(frag_file_name, &this->fragShader, PRINCIPAL_SHADER_SIZE);
    delete frag_file_name;
}

void Shader::Set_vert(const char* vert_file_name) noexcept
{
    ReadFile(vert_file_name, &this->vertShader, PRINCIPAL_SHADER_SIZE);
    delete vert_file_name;
}

void Shader::Guess_frag(const char* vfs_file_name) noexcept
{
    this->Set_frag(this->guesser(vfs_file_name, FRAG_END_FILE_NAME));
}

void Shader::Guess_vert(const char* vfs_file_name) noexcept
{
    this->Set_vert(this->guesser(vfs_file_name, VERT_END_FILE_NAME));
}

void Shader::CompileShader() noexcept
{   this->executeShaders(); }

void Shader::ConvertVFS(const char* VFS_filename) const
{   ConvertShaderExtension_GLSL(VFS_filename, 0); DEBUG(SHADER_LOG, "Fichier .vfs.glsl converti avec succès en .frag.glsl et en .vert.glsl.");   }

void Shader::Free() noexcept
{
    this->programID = 0;
    delete this->fragShader;
    delete this->vertShader;
}

    /// METHODES (private:)

const char* Shader::guesser(const char* vfs_file_name, const char* fragOrVert) noexcept
{
    long i = 0;
    fsimc(vfs_file_name, '.', &i);

    char* frag_file_name = (char*)malloc(i);
    int j = -1;
    while (++j < i)
        frag_file_name[j] = vfs_file_name[j];
    frag_file_name[j] = '\0';

    strcat(frag_file_name, fragOrVert);
    return (frag_file_name);
}

void Shader::executeShaders() noexcept
{
    GLuint vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShaderID, 1, &(this->vertShader), 0);
    glCompileShader(vertexShaderID);
    glShaderSource(fragmentShaderID, 1, &(this->fragShader), 0);
    glCompileShader(fragmentShaderID);

    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertexShaderID);
    glAttachShader(this->programID, fragmentShaderID);
    glLinkProgram(this->programID);

    glDetachShader(this->programID, vertexShaderID);
    glDetachShader(this->programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    delete this->vertShader;
    delete this->fragShader;
}