#ifndef PETRA_FTOPENGL_HPP
#define PETRA_FTOPENGL_HPP

#include <glad/glad.h>
#include <platforms/types_macros.hpp>

namespace ftOpenGL
{
        // Active l'attribut de shader spécifié à un certain index pour sa création ou son rendu
    #define activeAttributeArray(layout_index)      glEnableVertexAttribArray(layout_index)

        // Désactive l'attribut de shader spécifié à un certain index
    #define desactiveAttributeArray(layout_index)   glDisableVertexAttribArray(layout_index)

        // Active l'attribut de shader spécifié à un certain index pour sa création ou son rendu
    #define activeShaderLayout(layout_index)        glEnableVertexAttribArray(layout_index)

        // Désactive l'attribut de shader spécifié à un certain index
    #define desactiveShaderLayout(layout_index)     glDisableVertexAttribArray(layout_index)

        // lier, mettre des informations dans l'attribut de l'objet, se fait qu'une seule fois à la création de l'objet
    #define setAttributeArray       glVertexAttribPointer

        // Création d'un simple indentifiant OpenGL d'une array d'attribut
    void refID_AttributeArray(uint32& attributeArray_ID)   noexcept;

        // Créé un type (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, ...) de buffer et y met les données inclut dans les paramètres
        //
        // GL_METHOD_DRAW --> GL_STATIC_DRAW / GL_DYNAMIC_DRAW / GL_STREAM_DRAW
    void setBuffer(const uint32&& TYPE_OF_BUFFER, uint32& buffer_ID, const void* data, const int32& data_size, const uint32&& GL_METHOD_DRAW)    noexcept;

        // Sert simplement d'alias pour 'activeAttributeArray(vertex_layout_location)'
    void startRendering(const uint32& vertex_layout_location)  noexcept;

        // Explicite à la carte graphique que les données associéés à l'identifiant buffer_ID seront utilisées, pour par exemple drawRender
    void renderBuffer(const uint32& layout_location, const int32& dataLine_size, const uint32&& TYPE_OF_BUFFER, const int32& buffer_ID, const uint32& GL_TYPE_NATIF, const int32& stride, const void* ptr = ((const void*)0x0), const bool8& normalized = 0x0)   noexcept;

        // Utilise 'DrawArrays()' pour par la suite 'disableAttributeArrays(vertex_layout_location)'
    void drawRender(const uint32& vertex_layout_location, const uint& GL_WHATDRAW, const int& count, const int& first_index = 0)   noexcept;

        // Création d'un simple objet OpenGL
    void createSimpleOpenGLOBject(uint32& attributeArray_ID)     noexcept;

    //void attacheSharedTexture( ... ) noexcept;
    //void attacheSharedMatrix( ... ) noexcept;
}

#endif