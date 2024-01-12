#ifndef PETRA_SHADER_HPP
#define PETRA_SHADER_HPP

#include <glad/glad.h>

#include <C/ConvertFullShadertoGLSL.h>
#include <platforms/logs_macros.hpp>

#include <utils/f_utils.h>

#define PRINCIPAL_SHADER_SIZE    FILE_SIZE_1KO

#define FRAG_END_FILE_NAME       "frag.glsl"
#define VERT_END_FILE_NAME       "vert.glsl"

class Shader final
{
public:
        /// CONSTRUCTEURS

    Shader(const char* VFS_filename);
    Shader(const char* fragShader, const char* vertShader);
    Shader(const char* VFS_filename, const char* fragShader, const char* vertShader);
    ~Shader();

        /// METHODES

    const char* GetFragment() const noexcept;
    const char* GetVertex  () const noexcept;

    void Set_frag(const char* frag_file_name) noexcept;
    void Set_vert(const char* vert_file_name) noexcept;
    void Guess_frag       (const char* vfs_file_name)          noexcept;
    void Guess_vert       (const char* vfs_file_name)          noexcept;

    void            CompileShader()                                                                          noexcept;

    inline void UseShader() const noexcept 
    { glad_glUseProgram(this->programID); }

    void ConvertVFS(const char* VFS_filename) const;
    void Free      ()                         noexcept;

    GLuint  programID;
private:
    
        /// METHODES

    const char* guesser(const char* vfs_file_name, const char* fragOrVert) noexcept;
    void executeShaders() noexcept;

        /// ATTRIBUTS

    char* fragShader;
    char* vertShader;
};

#endif