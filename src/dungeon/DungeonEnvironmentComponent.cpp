#include "DungeonEnvironmentComponent.h"
#include "src/engine/common/system/TickSystem.h"

DungeonEnvironmentComponent::DungeonEnvironmentComponent()
{

}

DungeonEnvironmentComponent::~DungeonEnvironmentComponent()
{

}

void DungeonEnvironmentComponent::makeDungeonChunksFromMapSegment(std::shared_ptr<MapSegment> seg) {
    // split up the segment into 10 by 10 chunks
    for (int row = 0; row < MapGenerator::MAP_HEIGHT; row+=DUNGEON_CHUNK_SIZE) {
        for (int col = 0; col < MapGenerator::MAP_WIDTH; col+=DUNGEON_CHUNK_SIZE) {
            makeChunk(seg, row, col);
        }
    }
}

void DungeonEnvironmentComponent::addComponentToSystemsAndConnectComponents()
{
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->addComponent(this);
}

void DungeonEnvironmentComponent::removeComponentFromSystems() {
    m_gameobject->getGameWorld()->getSystem<TickSystem>()->removeComponent(this);
}

void DungeonEnvironmentComponent::makeChunk(std::shared_ptr<MapSegment> seg, int startrow, int startcol) {
    std::vector<float> vert_data;
    for (int row = startrow; row < startrow + DUNGEON_CHUNK_SIZE; row++) {
        for (int col = startcol; col < startcol + DUNGEON_CHUNK_SIZE; col++) {
            if (seg->data[row * MapGenerator::MAP_WIDTH + col] == WALL) {
                // make a cube with the appropriate texture
                DungeonEnvironmentData::fillVectorWithWallData(vert_data, row, col + seg->info.segment_num*MapGenerator::MAP_WIDTH,
                                                               0, 1, 0, 1);
            } else if (seg->data[row * MapGenerator::MAP_WIDTH + col] == OPEN) {
                //make a ceiling a floor with appropriate textures
            }
        }
    }
    if (vert_data.size() > 0) {
        std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(vert_data);
        m_gameobject->getComponent<ChunkDrawableComponent>()->addChunk(chunk);
    }
}

void DungeonEnvironmentComponent::tick(float seconds) {

}
