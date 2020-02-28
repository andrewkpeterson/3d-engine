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
    void enqueueDungeonChunksFromMapSegment(int seg_idx, std::shared_ptr<MapSegment> seg);
    void addSegment(std::shared_ptr<MapSegment> seg);
    bool buildChunk(int seg_idx, int startrow, int startcol, ChunkComponent* chunk);
    void tick(float seconds) override;

private:
    const int DUNGEON_CHUNK_SIZE = 5;
    float m_size;
    const float SEGMENT_LENGTH = 275.0f;
    int curr_segment;
    int farthest_back_segment;
    int farthest_ahead_segment;
    std::string atlas_name;
    std::vector<std::shared_ptr<MapSegment>> map_segments;
    std::map<int, std::unordered_set<std::shared_ptr<ChunkComponent>>> chunk_map;
};

#endif // DUNGEONENVIRONMENTCOMPONENT_H
