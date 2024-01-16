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

        // Mettre en place un shader :
        //  1 - shaderVar.SetVFS("path to a .vfs.glsl file")
        //  2 - Par la suite 'Guess_frag("path to a .vfs.glsl file")' et 'Guess_vert("path to a .vfs.glsl file")'
        //  3 - Pour finir shaderVar.CompileShader()
        // Plus précis :
        //  1 - Avec Set_frag("path to a .frag.glsl file") et Set_vert("path to a .vert.glsl file")
        //  2 - Pour finir shaderVar.CompileShader()
        // Plus rapide :
        //  1 - shaderVar.Make("path to a .vfs.glsl file")
    Shader() noexcept;
   ~Shader() noexcept;

    /// METHODES

    const char* GetFragment() const noexcept;
    const char* GetVertex  () const noexcept;

    int  Make               (const char* VFS_filename)     noexcept;
    int  SetVFS             (const char* VFS_filename)     noexcept;
    int  Set_frag           (const char* frag_file_name)   noexcept;
    int  Set_vert           (const char* vert_file_name)   noexcept;
    int  Guess_frag         (const char* vfs_file_name)    noexcept;
    int  Guess_vert         (const char* vfs_file_name)    noexcept;

    void CompileShader      ()                             noexcept;

    inline void UseShader   ()                      const  noexcept 
    { glad_glUseProgram(this->programID); }

    void ConvertVFS(const char* VFS_filename)       const          ;
    void Free      ()                                      noexcept;

    GLuint  programID;
private:
    
        /// METHODES

    int guesser(const char* vfs_file_name, char*& buffer, const char* fragOrVert) noexcept;
    void executeShaders() noexcept;

        /// ATTRIBUTS

    char* fragShader;
    char* vertShader;
};

#endif