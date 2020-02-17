#ifndef CHUNK_H
#define CHUNK_H

#include "Shape.h"

struct AABB {
    float x_neg;
    float x_pos;
    float y_neg;
    float y_pos;
    float z_neg;
    float z_pos;
};

class Chunk : public Shape
{
public:
    Chunk(const std::vector<float> &vertices);
    Chunk(const std::vector<float> &vertices, const std::vector<int> &faces);
    ~Chunk();

private:
    void setUpBoundingBox();
    AABB bounds;
};

#endif // CHUNK_H
