#ifndef VBOATTRIBMARKER_H
#define VBOATTRIBMARKER_H

#include <string>

#include "GL/glew.h"

struct VBOAttribMarker {
    enum DATA_TYPE{ FLOAT = GL_FLOAT, INT = GL_INT, UNSIGNED_BYTE = GL_UNSIGNED_BYTE, UNSIGNED_INT = GL_UNSIGNED_INT };
    enum DATA_NORMALIZE{ GLTRUE = GL_TRUE, GLFALSE = GL_FALSE };

    /**
     * @brief VBOAttribMarker
     * @param index OpenGL handle to the attribute location. These are specified in ShaderAttribLocations.h
     * @param numElementsPerVertex Number of elements per vertex. Must be 1, 2, 3 or 4 (e.g. position = 3 for x,y,z)
     * @param offset Offset in BYTES from the start of the array to the beginning of the first element
     * @param type Primitive type (FLOAT, INT, UNSIGNED_BYTE)
     * @param normalize
     */
    VBOAttribMarker(GLuint index, GLuint numElementsPerVertex, int offset, DATA_TYPE type = FLOAT, bool normalize = false);

    GLuint index;
    DATA_TYPE dataType;
    DATA_NORMALIZE dataNormalize;
    GLuint numElements;
    size_t offset;
};

#endif // VBOATTRIBMARKER_H
