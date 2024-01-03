#ifndef PETRA_SHADER_HPP
#define PETRA_SHADER_HPP

#include <glad/glad.h>

#include <C/ConvertFullShadertoGLSL.h>
#include <platforms/logs_macros.hpp>

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

    void Set_frag         (const char* frag)                   noexcept;
    void Set_vert         (const char* vert)                   noexcept;
    void Set_frag_set_vert(const char* frag, const char* vert) noexcept;

    void            CompileShader()                                                                          noexcept;
    static Shader   Precompile   (const char* VFS_filename, const char* fragShader, const char* vertShader)  noexcept;

    inline void UseShader() const noexcept 
    { glad_glUseProgram(this->programID); }

    void ConvertVFS(const char* VFS_filename) const;
    void Free      ()                         noexcept;

    GLuint  programID;
private:
    
        /// METHODES

    void executeShaders() noexcept;

        /// ATTRIBUTS

    char* fragShader;
    char* vertShader;
};

#endif