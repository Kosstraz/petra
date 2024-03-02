#include <base/Cube.hpp>

#define SHADER_PROG Handle::shadersProgram[0]

    /*////////////////////*/
    ///  CONSTRUCTEURS   ///
    /*////////////////////*/

Cube::Cube(const char* name) : GeometryTest(name)   , faceCount(0)  , vertexBuffersID(nullptr)  , uvsBuffersID(nullptr) , textureBuffersID(nullptr)
{
    this->vertexBuffersID   = (uint*)malloc(6 * sizeof(uint));
    this->uvsBuffersID      = (uint*)malloc(6 * sizeof(uint));
    this->textureBuffersID  = (uint*)malloc(6 * sizeof(uint));

    const char *textures[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    this->PutMultiplesTextures(textures);
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
    ftOpenGL::refID_AttributeArray(this->vertexArrayID);


    this->FrontFace ();
    this->BackFace  ();
    this->RightFace ();
    this->LeftFace  ();
    this->TopFace   ();
    this->BotFace   ();
}

void Cube::DrawBuild()    const    noexcept
{
    PushMatProgram(this->SP, "TRANSFORMATION", (-1));

    uint32 i = 0;
    while (i < 6)
    {
        ftOpenGL::startRendering(0);
        ftOpenGL::renderBuffer(0, 3, GL_ARRAY_BUFFER, this->vertexBuffersID[i], GL_FLOAT, 0);

        activeShaderLayout(1);
        ftOpenGL::renderBuffer(1U, 2, GL_ARRAY_BUFFER, this->uvsBuffersID[i], GL_FLOAT, 0);
        Texture::BindToShader(this->textureBuffersID[i]);

        int unifLoc = glGetUniformLocation(Handle::shadersProgram[0], "COLOR");
        glUniform4f(unifLoc, color.x, color.y, color.z, 1.0f);

        ftOpenGL::drawRender(0, GL_TRIANGLE_STRIP, 4);
        desactiveShaderLayout(1);
    }
}

void Cube::PutMultiplesTextures(const char* textureNames[6])  noexcept
{
    int8 count = -1;
    while (++count < 6)
    {
        if (textureNames[count] != nullptr)
        {
            for (ArrayForTexture::const_iterator i = global_textures.begin(); i != global_textures.end(); ++i)
                if (strcmp(textureNames[count], i->first) == 0)
                    this->textureBuffersID[count] = i->second;
        }
        else if (strcmp(textureNames[count], "no_texture") == 0)
            this->textureBuffersID[count] = UINT32_MAX_;
        else
            for (ArrayForTexture::const_iterator i = global_textures.begin(); i != global_textures.end(); ++i)
                if (strcmp("NULL/NULL.bmp", i->first) == 0)                                                           // ?(++global_textures.begin())->first
                    this->textureBuffersID[count] = i->second;
    }
}

void Cube::Destroy()  noexcept
{
        // delete vertex datas
    int8 i = -1;
    while (++i < this->faceCount)
        if (this->vertexBuffersID[i] != 0)
            glDeleteBuffers(1, &this->vertexBuffersID[i]);

        // delete (U, V)' datas
    i = -1;
    while (++i < this->faceCount)
        if (this->uvsBuffersID[i] != 0)
            glDeleteBuffers(1, &this->uvsBuffersID[i]);
    
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
    constexpr uint8 face_index = 0;

        // vertex
    constexpr float vertices[0xC] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

        // texture
    constexpr float uvsBufferData[8] = {
         1.0f, 0.0f,
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[face_index],  vertices,       sizeof(vertices),       GL_STREAM_DRAW);
    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[face_index],     uvsBufferData,  sizeof(uvsBufferData),  GL_STREAM_DRAW);
}

void Cube::BackFace()  noexcept
{
    constexpr uint8 face_index = 1;

        // vertex
    constexpr float vertices[0xC] = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f
    };

        // texture
    constexpr float uvsBufferData[8] = {
         0.0f, 0.0f,
         1.0f, 0.0f,
         0.0f, 1.0f,
         1.0f, 1.0f
    };

    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[face_index], vertices,      sizeof(vertices),      GL_STREAM_DRAW);
    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[face_index],    uvsBufferData, sizeof(uvsBufferData), GL_STREAM_DRAW);
}

void Cube::RightFace()  noexcept
{
    constexpr uint8 face_index = 2;

    constexpr float vertices[0xC] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  0.0f
    };

        // texture
    constexpr float uvsBufferData[8] = {
         1.0f, 0.0f,
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[face_index], vertices,      sizeof(vertices),      GL_STREAM_DRAW);
    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[face_index],    uvsBufferData, sizeof(uvsBufferData), GL_STREAM_DRAW);
}

void Cube::LeftFace()  noexcept
{
    constexpr uint8 face_index = 3;

    constexpr float vertices[0xC] = {
         1.0f, -1.0f,  0.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f
    };

        // texture
    constexpr float uvsBufferData[8] = {
         1.0f, 0.0f,
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[face_index], vertices,      sizeof(vertices),      GL_STREAM_DRAW);
    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[face_index],    uvsBufferData, sizeof(uvsBufferData), GL_STREAM_DRAW);
}

void Cube::TopFace()  noexcept
{
    constexpr uint8 face_index = 4;

    constexpr float vertices[0xC] = {
         -1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f
    };

        // texture
    constexpr float uvsBufferData[8] = {
         1.0f, 0.0f,
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[face_index], vertices,      sizeof(vertices),      GL_STREAM_DRAW);
    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[face_index],    uvsBufferData, sizeof(uvsBufferData), GL_STREAM_DRAW);
}

void Cube::BotFace()  noexcept
{
    constexpr uint8 face_index = 5;

    constexpr float vertices[0xC] = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  0.0f
    };

        // texture
    constexpr float uvsBufferData[8] = {
         1.0f, 0.0f,
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->vertexBuffersID[face_index], vertices,      sizeof(vertices),      GL_STREAM_DRAW);
    ftOpenGL::setBuffer(GL_ARRAY_BUFFER, this->uvsBuffersID[face_index],    uvsBufferData, sizeof(uvsBufferData), GL_STREAM_DRAW);
}