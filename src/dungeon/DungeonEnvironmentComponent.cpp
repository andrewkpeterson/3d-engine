#include "DungeonEnvironmentComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/component/StaticAABCollisionComponent.h"
#include "src/engine/common/component/ChunkComponent.h"

DungeonEnvironmentComponent::DungeonEnvironmentComponent(float size, std::string atlas) :
    m_size(size),
    atlas_name(atlas)
{

}

DungeonEnvironmentComponent::~DungeonEnvironmentComponent()
{

}

void DungeonEnvironmentComponent::enqueueDungeonChunksFromMapSegment(std::shared_ptr<MapSegment> seg) {
    // split up the segment into 10 by 10 chunks
    for (int row = 0; row < MapGenerator::MAP_HEIGHT; row+=DUNGEON_CHUNK_SIZE) {
        for (int col = 0; col < MapGenerator::MAP_WIDTH; col+=DUNGEON_CHUNK_SIZE) {
            std::shared_ptr<GameObject> new_chunk_object = std::make_shared<GameObject>();
            new_chunk_object->addComponent<ChunkComponent>(
                        std::make_shared<ChunkComponent>(std::bind(&DungeonEnvironmentComponent::buildChunk, this,
                                                                   seg, row, col, std::placeholders::_1)));
            new_chunk_object->addComponent<ChunkDrawableComponent>(std::make_shared<ChunkDrawableComponent>(atlas_name));
            new_chunk_object->addComponent<StaticAABCollisionComponent>(
                        std::make_shared<StaticAABCollisionComponent>(false, false, std::vector<AAB>({})));
            m_gameobject->getGameWorld()->addGameObject(new_chunk_object);
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

bool DungeonEnvironmentComponent::buildChunk(std::shared_ptr<MapSegment> seg, int startrow,
                                                               int startcol, ChunkComponent* chunk_comp) {
    std::vector<float> vert_data;
    std::vector<AAB> bounding_boxes;
    for (int row = startrow; row < startrow + DUNGEON_CHUNK_SIZE; row++) {
        for (int col = startcol; col < startcol + DUNGEON_CHUNK_SIZE; col++) {
            if (seg->data[row * MapGenerator::MAP_WIDTH + col] == WALL) {
                // make a cube with the appropriate texture
                bounding_boxes.push_back(
                            DungeonEnvironmentData::fillVectorWithWallData(vert_data, row,
                                                                           col + seg->info.segment_num*MapGenerator::MAP_WIDTH,
                                                                           4*.0625, 5*.0625, 13*.0625, 14*.0625));
            } else if (seg->data[row * MapGenerator::MAP_WIDTH + col] == OPEN) {
                //make a ceiling and floor with appropriate textures
                DungeonEnvironmentData::fillVectorWithCeilingData(vert_data, row, col + seg->info.segment_num*MapGenerator::MAP_WIDTH,
                                                                  0, .0625, 1-.0625, 1);
                DungeonEnvironmentData::fillVectorWithFloorData(vert_data, row, col + seg->info.segment_num*MapGenerator::MAP_WIDTH,
                                                                4*.0625, 5*.0625, 1-.0625, 1);
            }
        }
    }
    // scale all of the vertex positions so that the dungeon is the right size
    for (int i = 0; i < vert_data.size(); i+=8) {
        vert_data[i] *= m_size;
        vert_data[i+1] *= m_size;
        vert_data[i+2] *= m_size;
    }

    // scale all of the bounding boxes and add small buffer to their bounding boxes
    for (int i = 0; i < bounding_boxes.size(); i++) {
        bounding_boxes[i].neg *= m_size;
        bounding_boxes[i].pos *= m_size;
    }

    if (vert_data.size() > 0) {
        std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(vert_data);
        chunk_comp->setChunk(chunk);
        chunk_comp->getGameObject()->getComponent<StaticAABCollisionComponent>()->setBounds(bounding_boxes);
        chunk_comp->getGameObject()->getComponent<StaticAABCollisionComponent>()->setActive(true);
        return true;
    } else {
        return false;
    }
}

void DungeonEnvironmentComponent::tick(float seconds) {
    // create maps and enqueue chunks for streaming system
}
