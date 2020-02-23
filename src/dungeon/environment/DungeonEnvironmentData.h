#ifndef DUNGEONENVIRONMENTDATA_H
#define DUNGEONENVIRONMENTDATA_H

#include <vector>
#include "src/engine/common/component/AABCollisionComponent.h"

class DungeonEnvironmentData
{
public:
    DungeonEnvironmentData();
    ~DungeonEnvironmentData();

    static AAB fillVectorWithWallData(std::vector<float> &vertex_data, float topleft_x, float topleft_z,
                           float ustart, float uend, float vstart, float vend);
    static void fillVectorWithFloorData(std::vector<float> &vertex_data, float topleft_x, float topleft_z,
                            float ustart, float uend, float vstart, float vend);
    static void fillVectorWithCeilingData(std::vector<float> &vertex_data, float topleft_x, float topleft_z,
                              float ustart, float uend, float vstart, float vend);
};

#endif // DUNGEONENVIRONMENTDATA_H
