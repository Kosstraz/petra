#ifndef PETRA_RENDERERMANAGER_HPP
#define PETRA_RENDERERMANAGER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <core/Handle.hpp>

inline void PushMat(const glm::mat4& mat, const char* uniform_name)
{
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], uniform_name);
    glUniformMatrix4fv(unifLoc, 0x0001, 0x0000, &mat[0][0]);
}

inline void PushMatProgram(const glm::mat4& mat, const char* uniform_name, int shaderProgram = (-1))
{
    if (shaderProgram == (-1))
        shaderProgram = Handle::shadersProgram[0];
    glUseProgram(shaderProgram);

    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], uniform_name);
    glUniformMatrix4fv(unifLoc, 0x0001, 0x0000, &mat[0][0]);
}

#endif