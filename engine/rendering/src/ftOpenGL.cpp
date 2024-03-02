#include <rendering/ftOpenGL.hpp>

void ftOpenGL::refID_AttributeArray(uint32& attributeArray_ID)  noexcept
{
    glGenVertexArrays(1, &attributeArray_ID);
    glBindVertexArray(attributeArray_ID);
}

void ftOpenGL::setBuffer(const uint32&& TYPE_OF_BUFFER, uint32& buffer_ID, const void* data, const int32& data_size, const uint32&& GL_METHOD_DRAW) noexcept
{
    glGenBuffers(1, &buffer_ID);
    glBindBuffer(TYPE_OF_BUFFER, buffer_ID);
    glBufferData(TYPE_OF_BUFFER, data_size, data, GL_METHOD_DRAW);
}

void ftOpenGL::startRendering(const uint32& vertex_layout_location) noexcept
{
    activeShaderLayout(vertex_layout_location);
}

/**
    // * Si le param:layout_location n'est pas celui envoyé à 'startRendering()' (ni à 'drawRender()') il doit être spécifié avec 'activeAttributeArray(layout_location)' avant cette fonction et 
    // * 'desactiveAttributeArray(layout_location)' après la fonction 'drawRender()'
    // @param layout_location   Correspond à la position du layout de votre shader que vous convoitez
    // @param dataLine_size     Correspond à la taille d'une ligne, exemple si vous donner des coordonnées (X, Y, Z) alors dataLine_size = 3
    // @param TYPE_OF_BUFFER    GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, ...
    // @param buffer_ID         Quel buffer va être rendu
    // @param GL_TYPE_NATIF     GL_FLOAT, GL_UNSIGNED_BYTE, ...
    // @param stride            Indique le décalage à effectuer entre chaque donnée du tableau, 0 si les données sont consécutives
*/
void ftOpenGL::renderBuffer(const uint32& layout_location, const int32& dataLine_size, const uint32&& TYPE_OF_BUFFER, const int32& buffer_ID, const uint32& GL_TYPE_NATIF, const int32& stride, const void* ptr, const bool8& normalized) noexcept
{
    glBindBuffer(TYPE_OF_BUFFER, buffer_ID);
    glVertexAttribPointer(layout_location, dataLine_size, GL_TYPE_NATIF, normalized, stride, ptr);
}

void ftOpenGL::drawRender(const uint32& vertex_layout_location, const uint& GL_WHATDRAW, const int& count, const int& first_index) noexcept
{
    glDrawArrays(GL_WHATDRAW, first_index, count);
    desactiveShaderLayout(vertex_layout_location);
}

void ftOpenGL::createSimpleOpenGLOBject(uint32& attributeArray_ID) noexcept
{
    refID_AttributeArray(attributeArray_ID);

}