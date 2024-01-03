#include "../GeometryTest.hpp"

    /// CONSTRUCTEURS

GeometryTest::GeometryTest(const char* name) : PetraO(name), GL_GEOMETRY(0), vertexArrayID(0), vertexBufferID(0), verticesToDraw(0)
{
    this->model              = new Matrix4x4f(1.0f);
    this->transform.position = Vector3f(0.f, 0.f, 0.f);

    this->what_build = 0;
}

GeometryTest::~GeometryTest() noexcept
{
    this->Free();
}

    /// METHODES

void GeometryTest::WhatBuild(uint8 DRAW_WHAT) 
{
    this->what_build = DRAW_WHAT;
}

void GeometryTest::BuildTriangle(uint32 GL_METHOD_DRAW) noexcept
{
    constexpr float vertices[9] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f 
    };

        //GESTION DONNEES
    glad_glGenVertexArrays(1, &this->vertexArrayID);
    glad_glBindVertexArray(this->vertexArrayID);

    glad_glGenBuffers(1, &this->vertexBufferID);
    glad_glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_METHOD_DRAW);

    int unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "TRANSFORMATION");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->model->Ref());

    this->GL_GEOMETRY    = GL_TRIANGLES;
    this->verticesToDraw = 3;
}

void GeometryTest::BuildSquare(uint32 GL_METHOD_DRAW) noexcept
{
    constexpr float vertices[12] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

        //GESTION DONNEES
    glad_glGenVertexArrays(1, &this->vertexArrayID);
    glad_glBindVertexArray(this->vertexArrayID);

    glad_glGenBuffers(1, &this->vertexBufferID);
    glad_glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_METHOD_DRAW);

    int unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "TRANSFORMATION");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->model->Ref());

    this->GL_GEOMETRY    = GL_TRIANGLE_STRIP;
    this->verticesToDraw = 4;
}

void GeometryTest::BuildRectangle(uint32 GL_METHOD_DRAW) noexcept
{

}

void GeometryTest::Build(uint32 GL_METHOD_DRAW) noexcept
{
    switch (this->what_build)
    {
        case 0:
            this->BuildTriangle(GL_METHOD_DRAW);
            break;
        case 1:
            this->BuildSquare(GL_METHOD_DRAW);
            break;
        case 2:
            this->BuildRectangle(GL_METHOD_DRAW);
            break;
        default:
            throw ("Nothing to build");
            break;
    }
}

void GeometryTest::DrawBuild() noexcept
{
    glad_glUseProgram(Handle::shadersProgram[0]);

    glad_glEnableVertexAttribArray(0);
    glad_glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, ((const void*)0));
    glad_glDrawArrays(this->GL_GEOMETRY, 0, this->verticesToDraw);
    glad_glDisableVertexAttribArray(0);
}

void GeometryTest::SetPosition(const Vector3f position) noexcept
{
    this->transform.position = position;
    this->model->Translation(position);

    int unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "TRANSFORMATION");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->model->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}

void GeometryTest::SetScale(const Vector3f scale) noexcept
{
    this->transform.scale = scale;
    this->model->Scale(scale);

    int unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "TRANSFORMATION");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->model->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}

void GeometryTest::SetRotation(const Vector3f rotation) noexcept
{
    this->transform.rotation = rotation;
    this->model->Rotation(rotation);

    int unifLoc = glad_glGetUniformLocation(Handle::shadersProgram[0], "TRANSFORMATION");
    glad_glUniformMatrix4fv(unifLoc, 1, false, this->model->Ref());

    glad_glUseProgram(Handle::shadersProgram[0]);
}

inline void GeometryTest::Free() noexcept
{
    delete this->model;
}