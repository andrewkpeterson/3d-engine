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
    float x_neg = m_positions[0];
    float y_neg = m_positions[1];
    float z_neg = m_positions[2];
    float x_pos = m_positions[0];
    float y_pos = m_positions[1];
    float z_pos = m_positions[2];
    for (int i = 0; i < m_positions.size(); i+=3) {
        if (x_neg > m_positions[i]) {
            x_neg = m_positions[i];
        }
        if (y_neg > m_positions[i+1]) {
            y_neg = m_positions[i+1];
        }
        if (z_neg > m_positions[i+2]) {
            z_neg = m_positions[i+2];
        }
        if (x_pos < m_positions[i]) {
            x_pos = m_positions[i];
        }
        if (y_pos < m_positions[i+1]) {
            y_pos = m_positions[i+1];
        }
        if (z_pos < m_positions[i+2]) {
            z_pos = m_positions[i+2];
        }
    }
    bounds.push_back(glm::vec4(x_neg, y_neg, z_neg, 1.0));
    bounds.push_back(glm::vec4(x_pos, y_neg, z_neg, 1.0));
    bounds.push_back(glm::vec4(x_neg, y_pos, z_neg, 1.0));
    bounds.push_back(glm::vec4(x_neg, y_neg, z_pos, 1.0));
    bounds.push_back(glm::vec4(x_pos, y_pos, z_neg, 1.0));
    bounds.push_back(glm::vec4(x_neg, y_pos, z_pos, 1.0));
    bounds.push_back(glm::vec4(x_pos, y_neg, z_pos, 1.0));
    bounds.push_back(glm::vec4(x_pos, y_pos, z_pos, 1.0));
}

Chunk::~Chunk()
{

}

const std::vector<glm::vec4> &Chunk::getBounds() {
    return bounds;
}
