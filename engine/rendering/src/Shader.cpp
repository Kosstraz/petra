#include "../Shader.hpp"

    /// CONSTRUCTEURS

Shader::Shader(const char* VFS_filename)
{
    this->programID  = 0;
    this->fragShader = ((char*)0);
    this->vertShader = ((char*)0);
    
    ConvertShaderExtension_GLSL(VFS_filename, LARGE_FILE_SIZE);
    DEBUG(SHADER_LOG, "Fichier .vfs.glsl converti avec succes en .frag.glsl et en .vert.glsl.");

    delete VFS_filename;
}

Shader::Shader(const char* fragShader, const char* vertShader)
{
    this->programID  = 0;
    this->fragShader = ((char*)0);
    this->vertShader = ((char*)0);
    
    ReadFile(fragShader, &this->fragShader, LARGE_FILE_SIZE);
    ReadFile(vertShader, &this->vertShader, LARGE_FILE_SIZE);
    DEBUG(SHADER_LOG, "Fichier .glsl lu avec succes, avec une taille maximale de 5096 bits.");
    
    delete fragShader;
    delete vertShader;
}

Shader::Shader(const char* VFS_filename, const char* fragShader, const char* vertShader)
{
    this->programID  = 0;
    this->fragShader = ((char*)0);
    this->vertShader = ((char*)0);
    
    ConvertShaderExtension_GLSL(VFS_filename, LARGE_FILE_SIZE);
    ReadFile(fragShader, &this->fragShader,   LARGE_FILE_SIZE);
    ReadFile(vertShader, &this->vertShader,   LARGE_FILE_SIZE);
    DEBUG(SHADER_LOG, "Fichier .glsl lu avec succes, avec une taille maximale de 5096 bits.");
    
    delete VFS_filename;
    delete fragShader;
    delete vertShader;
}

Shader::~Shader()
{   this->Free();   }

    /// METHODES

const char* Shader::GetFragment() const noexcept
{   return this->fragShader;  }

const char* Shader::GetVertex() const noexcept
{   return this->vertShader;    }

void Shader::Set_frag(const char* frag) noexcept
{
    ReadFile(frag, &this->fragShader, LARGE_FILE_SIZE);
    delete frag;
}

void Shader::Set_vert(const char* vert) noexcept
{
    ReadFile(vert, &this->vertShader, LARGE_FILE_SIZE);
    delete vert;
}

void Shader::Set_frag_set_vert(const char* frag, const char* vert) noexcept
{
    this->Set_frag(frag);
    delete frag;

    this->Set_vert(vert);
    delete vert;
}

void Shader::CompileShader() noexcept
{   this->executeShaders(); }

Shader Shader::Precompile(const char* VFS_filename, const char* fragShader, const char* vertShader) noexcept
{
    Shader ret = Shader(VFS_filename, fragShader, vertShader);
    ret.CompileShader();
    return ret;
}

void Shader::ConvertVFS(const char* VFS_filename) const
{   ConvertShaderExtension_GLSL(VFS_filename, 0); DEBUG(SHADER_LOG, "Fichier .vfs.glsl converti avec succès en .frag.glsl et en .vert.glsl.");   }

void Shader::Free() noexcept
{
    this->programID = 0;
    delete this->fragShader;
    delete this->vertShader;
}

    /// METHODES (private:)

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