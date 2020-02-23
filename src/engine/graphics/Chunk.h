#ifndef CHUNK_H
#define CHUNK_H

#include "Shape.h"

class Chunk : public Shape
{
public:
    Chunk(const std::vector<float> &vertices);
    Chunk(const std::vector<float> &vertices, const std::vector<int> &faces);
    ~Chunk();

    const std::vector<glm::vec4> &getBounds();

private:
    void setUpBoundingBox();
    std::vector<glm::vec4> bounds;
};

#endif // CHUNK_H
