#include "DungeonEnvironmentComponent.h"
#include "src/engine/common/system/TickSystem.h"

DungeonEnvironmentComponent::DungeonEnvironmentComponent(float size, std::string atlas) :
    m_size(size),
    atlas_name(atlas)
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
                                                               4*.0625, 5*.0625, 13*.0625, 14*.0625);
            } else if (seg->data[row * MapGenerator::MAP_WIDTH + col] == OPEN) {
                //make a ceiling and floor with appropriate textures
                DungeonEnvironmentData::fillVectorWithCeilingData(vert_data, row, col + seg->info.segment_num*MapGenerator::MAP_WIDTH,
                                                               0, .0625, 1-.0625, 1);
                DungeonEnvironmentData::fillVectorWithFloorData(vert_data, row, col + seg->info.segment_num*MapGenerator::MAP_WIDTH,
                                                               4*.0625, 5*.0625, 1-.0625, 1);
            }
        }
    }
    for (int i = 0; i < vert_data.size(); i+=8) {
        vert_data[i] *= m_size;
        vert_data[i+1] *= m_size;
        vert_data[i+2] *= m_size;
    }
    if (vert_data.size() > 0) {
        std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(vert_data);
        std::shared_ptr<GameObject> new_chunk_object = std::make_shared<GameObject>();
        new_chunk_object->addComponent<ChunkDrawableComponent>(std::make_shared<ChunkDrawableComponent>(chunk, atlas_name));
        m_gameobject->getGameWorld()->addGameObject(new_chunk_object);
    }
}

void DungeonEnvironmentComponent::tick(float seconds) {

}
