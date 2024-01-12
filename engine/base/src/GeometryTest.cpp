#include "../GeometryTest.hpp"

//#include <iostream>
#include <rendering/RendererManager.hpp>

    /*////////////////*/
    /// CONSTRUCTEUR ///
    /*////////////////*/



GeometryTest::GeometryTest(const char* name) : PetraO(name), GL_GEOMETRY(0), vertexArrayID(0), vertexBufferID(0), verticesToDraw(0)
{
    this->transform.position = Vector3f(0.f, 0.f, 0.f);
    this->MOD                = glm::mat4(1.0f);

    this->what_build = 0;
}

GeometryTest::~GeometryTest() noexcept
{
    this->Destroy();
}



    /*////////////*/
    /// METHODES ///
    /*////////////*/



void GeometryTest::WhatBuild(uint8 DRAW_WHAT) 
{
    this->what_build = DRAW_WHAT;
}

void GeometryTest::BuildTriangle(uint32 GL_METHOD_DRAW) noexcept
{
    glUseProgram(Handle::shadersProgram[0]);

    constexpr float vertices[9] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f 
    };

        // GESTION DONNEES
    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_METHOD_DRAW);

    PushMat(this->MOD, "TRANSFORMATION");

    this->GL_GEOMETRY    = GL_TRIANGLES;
    this->verticesToDraw = 3;
}

void GeometryTest::BuildSquare(uint32 GL_METHOD_DRAW) noexcept
{
    glUseProgram(Handle::shadersProgram[0]);

    constexpr float vertices[12] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

        // GESTION DONNEES
    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_METHOD_DRAW);

    PushMat(this->MOD, "TRANSFORMATION");

    this->GL_GEOMETRY    = GL_TRIANGLE_STRIP;
    this->verticesToDraw = 4;
}

void GeometryTest::BuildCube(uint32 GL_METHOD_DRAW) noexcept
{
    glUseProgram(Handle::shadersProgram[0]);

    constexpr uint8 vertexSize = (12 * 6);
    constexpr float vertices[vertexSize] = {
            // Avant
        -1.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,

            // Droite
         1.0f, -1.0f,  0.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f,

            // Bot
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,

            // Top
        -1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,

            // Left
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  0.0f,

            // Back
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f
    };

        // GESTION DONNEES
    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_METHOD_DRAW);

    PushMat(this->MOD, "TRANSFORMATION");

    this->GL_GEOMETRY    = GL_TRIANGLE_STRIP;
    this->verticesToDraw = (4 * 6);
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
            this->BuildCube(GL_METHOD_DRAW);
            break;
        default:
            break;
    }
}

void GeometryTest::DrawBuild() noexcept
{
    PushMatProgram(this->MOD, "TRANSFORMATION", (-1));
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "COLOR");
    glUniform4f(unifLoc, this->color.x, this->color.y, this->color.z, 1.0f);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, ((const void*)0));
    glDrawArrays(this->GL_GEOMETRY, 0, this->verticesToDraw);
    glDisableVertexAttribArray(0);
}

void GeometryTest::PutTexture(uint32 textureID) noexcept
{
    /*constexpr float g_uv_buffer_data[vertexSize] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f  
    };

     // GESTION TEXTURE
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &this->uvsBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvsBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_METHOD_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    texture.BindToShader();*/
}



void GeometryTest::SetPosition(const Vector3f& position) noexcept
{
    this->transform.position = position;
    this->MOD = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));

    PushMatProgram(this->MOD, "TRANSFORMATION", (-1));
}

void GeometryTest::SetScale(const Vector3f& scale) noexcept
{
    this->transform.scale = scale;
    this->MOD = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

    PushMatProgram(this->MOD, "TRANSFORMATION", (-1));
}

void GeometryTest::SetRotation(const Vector3f& rotation) noexcept
{
    //this->transform.rotation = rotation;
    //glm::mat4 ROT = glm::rotate(glm::quat(rotation.x, rotation.y, rotation.z), 90.0f, glm::vec3());
    //this->MOD = (ROT * MOD);

    PushMatProgram(this->MOD, "TRANSFORMATION", (-1));
}

void GeometryTest::SetColor(const Vector3f color) noexcept
{
    this->color = color;

    glUseProgram(Handle::shadersProgram[0]);
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "COLOR");
    glUniform4f(unifLoc, color.x, color.y, color.z, 1.0f);
}


inline void GeometryTest::Destroy() noexcept
{}