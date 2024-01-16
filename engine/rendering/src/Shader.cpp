#include "../Shader.hpp"

    /// CONSTRUCTEURS
Shader::Shader() noexcept : programID(0), fragShader(nullptr), vertShader(nullptr)
{}

Shader::~Shader()
{   this->Free();   }

    /// METHODES

const char* Shader::GetFragment()   const   noexcept
{   return (this->fragShader);  }

const char* Shader::GetVertex()     const   noexcept
{   return (this->vertShader);    }

int Shader::Make(const char* VFS_filename) noexcept
{
    int log = 0;
    if ((log = this->SetVFS(VFS_filename)) < 0)
        return_error("logVFS : ", log);
    this->Guess_frag(VFS_filename);
    this->Guess_vert(VFS_filename);
    this->CompileShader();
    
    return (0);
}

int Shader::SetVFS(const char* VFS_filename) noexcept
{
    int log = ConvertShaderExtension_GLSL(VFS_filename, PRINCIPAL_SHADER_SIZE);
    if (log < 0)
        return (log);

    DEBUG(SHADER_LOG, "Fichier .vfs.glsl converti avec succes");
    return (0);
}

int Shader::Set_frag(const char* frag_file_name) noexcept
{   return ReadFile(frag_file_name, this->fragShader, PRINCIPAL_SHADER_SIZE);}

int Shader::Set_vert(const char* vert_file_name) noexcept
{   return ReadFile(vert_file_name, this->vertShader, PRINCIPAL_SHADER_SIZE);}

int Shader::Guess_frag(const char* vfs_file_name) noexcept
{
    char* fragFile_name;
    this->guesser(vfs_file_name, fragFile_name, FRAG_END_FILE_NAME);
    this->Set_frag(fragFile_name);
    delete[] (fragFile_name);
    fragFile_name = nullptr;
}

int Shader::Guess_vert(const char* vfs_file_name) noexcept
{
    char* vertFile_name;
    this->guesser(vfs_file_name, vertFile_name, VERT_END_FILE_NAME);
    this->Set_vert(vertFile_name);
    delete[] (vertFile_name);
    vertFile_name = nullptr;
}

void Shader::CompileShader() noexcept
{   this->executeShaders(); }

void Shader::ConvertVFS(const char* VFS_filename) const
{   ConvertShaderExtension_GLSL(VFS_filename, 0); DEBUG(SHADER_LOG, "Fichier .vfs.glsl converti avec succès en .frag.glsl et en .vert.glsl.");   }

void Shader::Free() noexcept
{
    if (this->fragShader != nullptr)
    {
        free(this->fragShader);
        this->fragShader = nullptr;
    }
    if (this->vertShader != nullptr)
    {
        free(this->vertShader);
        this->vertShader = nullptr;
    }
}

    /// METHODES (private:)

int Shader::guesser(const char* vfs_file_name, char*& buffer, const char* fragOrVert) noexcept
{
    long i = 0;
    fsimc(vfs_file_name, '.', &i);

    buffer = new char[i + 9];
    if (buffer == nullptr)
        return SHADER_BAD_GUESSING;
    int j = -1;
    while (++j < i)
    { 
        buffer[j] = vfs_file_name[j];
    }
    buffer[j] = '\0';

    strcat(buffer, fragOrVert);
    return (0);
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

    this->Free();
}