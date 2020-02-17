#include "Chunk.h"

Chunk::Chunk(const std::vector<float> &vertices) :
    Shape(vertices)
{
    assert(vertices.size() % 8 == 0);
    setUpBoundingBox();
}

Chunk::Chunk(const std::vector<float> &vertices, const std::vector<int> &faces) :
    Shape(vertices, faces)
{
    assert(vertices.size() % 8 == 0);
    assert(faces.size() % 6 == 0);
    setUpBoundingBox();
}

void Chunk::setUpBoundingBox() {
    bounds.x_neg = m_positions[0];
    bounds.y_neg = m_positions[1];
    bounds.z_neg = m_positions[2];
    bounds.x_pos = m_positions[0];
    bounds.y_pos = m_positions[1];
    bounds.z_pos = m_positions[2];
    for (int i = 0; i < m_positions.size(); i+=3) {
        if (bounds.x_neg > m_positions[i]) {
            bounds.x_neg = m_positions[i];
        }
        if (bounds.y_neg > m_positions[i+1]) {
            bounds.y_neg = m_positions[i+1];
        }
        if (bounds.z_neg > m_positions[i+2]) {
            bounds.z_neg = m_positions[i+2];
        }
        if (bounds.x_pos < m_positions[i]) {
            bounds.x_pos = m_positions[i];
        }
        if (bounds.y_pos < m_positions[i+1]) {
            bounds.y_pos = m_positions[i+1];
        }
        if (bounds.z_pos < m_positions[i+2]) {
            bounds.z_pos = m_positions[i+2];
        }
    }
}

Chunk::~Chunk()
{

}
