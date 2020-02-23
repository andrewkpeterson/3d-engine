#include "DungeonEnvironmentData.h"

DungeonEnvironmentData::DungeonEnvironmentData()
{

}

DungeonEnvironmentData::~DungeonEnvironmentData()
{

}

AAB DungeonEnvironmentData::fillVectorWithWallData(std::vector<float> &vertex_data, float topleft_x, float topleft_z,
                                                  float ustart, float uend, float vstart, float vend) {
    vertex_data.insert(vertex_data.end(),
   {-0.5f + topleft_x, 0.0, 0.5f + topleft_z, 0, 0, 1, ustart, vstart,
    0.5f + topleft_x,  0.0f, 0.5f + topleft_z, 0, 0, 1, uend, vstart,
    0.5f + topleft_x,  1.0f, 0.5f + topleft_z, 0, 0, 1, uend, vend,
   -0.5f + topleft_x,  0.0f, 0.5f + topleft_z, 0, 0, 1, ustart, vstart,
    0.5f + topleft_x,  1.0f, 0.5f + topleft_z, 0, 0, 1, uend, vend,
   -0.5f + topleft_x,  1.0f, 0.5f + topleft_z, 0, 0, 1, ustart, vend,
   // top
   -0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 0, 1, 0, ustart, vstart,
    0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 0, 1, 0, uend, vstart,
    0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 0, 1, 0, uend, vend,
   -0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 0, 1, 0, ustart, vstart,
    0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 0, 1, 0, uend, vend,
   -0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 0, 1, 0, ustart, vend,
   // back
    0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, 0, -1, ustart, vstart,
   -0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, 0, -1, uend, vstart,
   -0.5f + topleft_x,  1.0f, -0.5f + topleft_z, 0, 0, -1, uend, vend,
    0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, 0, -1, ustart, vstart,
   -0.5f + topleft_x,  1.0f, -0.5f + topleft_z, 0, 0, -1, uend, vend,
    0.5f + topleft_x,  1.0f, -0.5f + topleft_z, 0, 0, -1, ustart, vend,
   // bottom
   -0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, -1, 0, ustart, vstart,
    0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, -1, 0, uend, vstart,
    0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 0, -1, 0, uend, vend,
   -0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, -1, 0, ustart, vstart,
    0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 0, -1, 0, uend, vend,
   -0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 0, -1, 0, ustart, vend,
   // left
   -0.5f + topleft_x, 0.0f, -0.5f + topleft_z, -1, 0, 0, ustart, vstart,
   -0.5f + topleft_x, 0.0f,  0.5f + topleft_z, -1, 0, 0, uend, vstart,
   -0.5f + topleft_x, 1.0f,  0.5f + topleft_z, -1, 0, 0, uend, vend,
   -0.5f + topleft_x, 0.0f, -0.5f + topleft_z, -1, 0, 0, ustart, vstart,
   -0.5f + topleft_x, 1.0f,  0.5f + topleft_z, -1, 0, 0, uend, vend,
   -0.5f + topleft_x, 1.0f, -0.5f + topleft_z, -1, 0, 0, ustart, vend,
   // right
    0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 1, 0, 0, ustart, vstart,
    0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 1, 0, 0, uend, vstart,
    0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 1, 0, 0, uend, vend,
    0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 1, 0, 0, ustart, vstart,
    0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 1, 0, 0, uend, vend,
    0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 1, 0, 0, ustart, vend});


    return AAB({glm::vec3(0.5f + topleft_x, 1.0f, 0.5f + topleft_z), glm::vec3(-0.5f + topleft_x, 0.0f, -0.5f + topleft_z)});
}

void DungeonEnvironmentData::fillVectorWithFloorData(std::vector<float> &vertex_data, float topleft_x, float topleft_z,
                                                float ustart, float uend, float vstart, float vend) {
    vertex_data.insert(vertex_data.end(),
    {-0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 0, 1, 0, ustart, vstart,
     0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 0, 1, 0, uend, vstart,
     0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, 1, 0, uend, vend,
    -0.5f + topleft_x, 0.0f,  0.5f + topleft_z, 0, 1, 0, ustart, vstart,
     0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, 1, 0, uend, vend,
    -0.5f + topleft_x, 0.0f, -0.5f + topleft_z, 0, 1, 0, ustart, vend,});

}

void DungeonEnvironmentData::fillVectorWithCeilingData(std::vector<float> &vertex_data, float topleft_x, float topleft_z,
                                               float ustart, float uend, float vstart, float vend) {

    vertex_data.insert(vertex_data.end(),
    {-0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 0, -1, 0, ustart, vstart,
     0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 0, -1, 0, uend, vstart,
     0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 0, -1, 0, uend, vend,
    -0.5f + topleft_x, 1.0f, -0.5f + topleft_z, 0, -1, 0, ustart, vstart,
     0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 0, -1, 0, uend, vend,
    -0.5f + topleft_x, 1.0f,  0.5f + topleft_z, 0, -1, 0, ustart, vend});
}
