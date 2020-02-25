#ifndef DUNGEONENVIRONMENTCOMPONENT_H
#define DUNGEONENVIRONMENTCOMPONENT_H

#include "src/engine/graphics/Chunk.h"
#include "src/engine/common/component/ChunkDrawableComponent.h"
#include "src/engine/common/component/Component.h"
#include "src/dungeon/environment/DungeonEnvironmentData.h"
#include "src/engine/common/map/MapGenerator.h"
#include "src/engine/common/component/TickComponent.h"
#include "src/engine/common/component/ChunkComponent.h"

class DungeonEnvironmentComponent : public TickComponent
{
public:
    DungeonEnvironmentComponent(float size, std::string atlas);
    ~DungeonEnvironmentComponent() override;

    virtual void addComponentToSystemsAndConnectComponents() override;
    virtual void removeComponentFromSystems() override;
    void enqueueDungeonChunksFromMapSegment(std::shared_ptr<MapSegment> seg);
    bool buildChunk(std::shared_ptr<MapSegment> seg, int startrow, int startcol, ChunkComponent* chunk);
    void tick(float seconds) override;

private:
    const int DUNGEON_CHUNK_SIZE = 5;
    float m_size;
    const float SEGMENT_LENGTH = 275.0f;
    int farthest_ahead_active_seg;
    int farthest_behind_active_seg;
    int map_seed;
    std::string atlas_name;
    std::vector<std::shared_ptr<MapSegment>> map_segments;
};

#endif // DUNGEONENVIRONMENTCOMPONENT_H
