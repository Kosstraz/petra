#include <base/Cube.hpp>

#define SHADER_PROG Handle::shadersProgram[0]

    /*////////////////////*/
    ///  CONSTRUCTEURS   ///
    /*////////////////////*/

Cube::Cube(const char* name) : GeometryTest(name)   , faceCount(0)  , vertexBuffersID(nullptr)  , uvsBuffersID(nullptr) , textureBuffersID(nullptr)
{
    vertexBuffersID  = (uint*)malloc(6);
}

Cube::~Cube()
{
    this->Destroy();
}

    /*////////////////*/
    ///   METHODES   ///
    /*////////////////*/

void Cube::Build(uint32 GL_METHOD_DRAW)    noexcept
{
    glUseProgram(SHADER_PROG);

    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    this->FrontFace ();
    //this->BackFace  ();
    //this->RightFace ();
    //this->LeftFace  ();
    //this->TopFace   ();
    //this->BotFace   ();
}

void Cube::DrawBuild()    const    noexcept
{
    PushMatProgram(this->SP, "TRANSFORMATION", (-1));
    int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "COLOR");
    glUniform4f(unifLoc, this->color.x, this->color.y, this->color.z, 1.0f);

    glEnableVertexAttribArray(0);
    uint8 i = 0;
    while (i < this->faceCount)
    {
        if (this->vertexBuffersID[i] != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i++]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, ((const void*)0));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
        else    i++;
    }
    glDisableVertexAttribArray(0);
}

void Cube::PutMultiplesTextures(const char* textureNames[6])  noexcept
{
    this->textureBuffersID = (uint*)malloc(6);
    int8 count = -1;
    while (++count < 6)
        if (textureNames[count] != nullptr)
                this->textureBuffersID[count] = global_rendering::textures[textureNames[count]];
        else    this->textureBuffersID[count] = 0;

    uvsBuffersID = (uint*)malloc(6);
}

void Cube::Destroy()  noexcept
{
        // delete vertex datas
    int8 i = -1;
    while (++i < this->faceCount)
        if (this->vertexBuffersID[i] != 0)
            glDeleteVertexArrays(1, &this->vertexBuffersID[i]);

        // delete (U, V)' datas
    i = -1;
    while (++i < this->faceCount)
        if (this->uvsBuffersID[i] != 0)
            glDeleteVertexArrays(1, &this->uvsBuffersID[i]);

        // delete vertex array datas
    if (this->vertexArrayID != 0)
        glDeleteVertexArrays(1, &this->vertexArrayID);

        // delete vertex buffer
    if (this->vertexBuffersID != nullptr)
    {
        free(this->vertexBuffersID);
        this->vertexBuffersID = nullptr;
    }
        // delete (U, V)' buffer
    if (this->uvsBuffersID != nullptr)
    {
        free(this->uvsBuffersID);
        this->uvsBuffersID = nullptr;
    }
        // delete (U, V)' buffer
    if (this->textureBuffersID != nullptr)
    {
        free(this->textureBuffersID);
        this->textureBuffersID = nullptr;
    }
}

    ///////////////////
    ////  PRIVATE   ///
    ///////////////////

void Cube::FrontFace()  noexcept
{
    const uint8 i = this->faceCount;

    constexpr uint32 vSize               = 0xC;
    constexpr float vertices[vSize] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    glEnableVertexAttribArray(0);
    glGenBuffers(1, &this->vertexBuffersID[i]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glDisableVertexAttribArray(0);

    constexpr float uvsBufferData[8] = {
        0.0f, 0.0f,
        -1.0f, 0.0f,
        0.0f, 1.0f,
        -1.0f, 1.0f
    };

    glEnableVertexAttribArray(1);
    glGenBuffers(1, &this->uvsBuffersID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvsBufferData), uvsBufferData, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    Texture::BindToShader(this->textureBuffersID[0]);
    //glDisableVertexAttribArray(1);

    this->faceCount++;
}

void Cube::BackFace()  noexcept
{
    const uint8 i = this->faceCount;

    constexpr uint32 vSize               = 0xC;
    constexpr float vertices[vSize] = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f
    };

    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBuffersID[i]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    this->faceCount++;
}

void Cube::RightFace()  noexcept
{
    const uint8 i = this->faceCount;

    constexpr uint32 vSize               = 0xC;
    constexpr float vertices[vSize] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  0.0f
    };

    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBuffersID[i]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    this->faceCount++;
}

void Cube::LeftFace()  noexcept
{
    const uint8 i = this->faceCount;

    constexpr uint32 vSize               = 0xC;
    constexpr float vertices[vSize] = {
         1.0f, -1.0f,  0.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f
    };

    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBuffersID[i]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    this->faceCount++;
}

void Cube::TopFace()  noexcept
{
    const uint8 i = this->faceCount;

    constexpr uint32 vSize               = 0xC;
    constexpr float vertices[vSize] = {
         -1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f
    };

    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBuffersID[i]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    this->faceCount++;
}

void Cube::BotFace()  noexcept
{
    const uint8 i = this->faceCount;

    constexpr uint32 vSize               = 0xC;
    constexpr float vertices[vSize] = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  0.0f
    };

    glGenVertexArrays(1, &this->vertexArrayID);
    glBindVertexArray(this->vertexArrayID);

    glGenBuffers(1, &this->vertexBuffersID[i]);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    this->faceCount++;
}