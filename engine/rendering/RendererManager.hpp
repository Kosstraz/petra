#ifndef PETRA_RENDERERMANAGER_HPP
#define PETRA_RENDERERMANAGER_HPP

#include <glad/glad.h>
#include <maths/Matrix.hpp>

#include <core/Handle.hpp>

#include <platforms/logs_macros.hpp>

inline void PushMat(Matrix4* mat, const char* uniform_name)
{
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], uniform_name);
    glUniformMatrix4fv(unifLoc, 1, false, &(mat->datas[0]));
}

inline void PushMatProgram(Matrix4* mat, const char* uniform_name, int shaderProgram = (-1))
{
    unsigned int sP;
    if (shaderProgram == (-1))
        sP = Handle::shadersProgram[0];
    glUseProgram(sP);

    int unifLoc = glGetUniformLocation(sP, uniform_name);
    glUniformMatrix4fv(unifLoc, 1, false, &(mat->datas[0]));
}

#endif