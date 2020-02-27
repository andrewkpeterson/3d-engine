#include "DungeonEnvironmentComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/component/StaticAABCollisionComponent.h"
#include "src/engine/common/component/ChunkComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"

DungeonEnvironmentComponent::DungeonEnvironmentComponent(float size, std::string atlas) :
    m_size(size),
    atlas_name(atlas),
    map_seed(100),
    farthest_ahead_active_seg(2),
    farthest_behind_active_seg(0)

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
    glm::vec3 pos = glm::vec3(startrow, 0, startcol + (seg->info.seed - 1)*MapGenerator::MAP_WIDTH) * m_size;
    for (int row = startrow; row < startrow + DUNGEON_CHUNK_SIZE; row++) {
        for (int col = startcol; col < startcol + DUNGEON_CHUNK_SIZE; col++) {
            if (seg->data[row * MapGenerator::MAP_WIDTH + col] == WALL) {
                // make a cube with the appropriate texture
                bounding_boxes.push_back(
                            DungeonEnvironmentData::fillVectorWithWallData(vert_data, row,
                                                                           col + (seg->info.seed - 1)*MapGenerator::MAP_WIDTH,
                                                                           4*.0625, 5*.0625, 13*.0625, 14*.0625));
            } else if (seg->data[row * MapGenerator::MAP_WIDTH + col] == OPEN) {
                //make a ceiling and floor with appropriate textures
                DungeonEnvironmentData::fillVectorWithCeilingData(vert_data, row, col + (seg->info.seed - 1)*MapGenerator::MAP_WIDTH,
                                                                  0, .0625, 1-.0625, 1);
                DungeonEnvironmentData::fillVectorWithFloorData(vert_data, row, col + (seg->info.seed - 1)*MapGenerator::MAP_WIDTH,
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
        chunk_comp->getGameObject()->getComponent<TransformComponent>()->setPos(pos);
        return true;
    } else {
        return false;
    }
}

void DungeonEnvironmentComponent::tick(float seconds) {
    // create maps and enqueue chunks for streaming system
    //std::cout << "farthest ahead" << std::endl;
    //std::cout << farthest_ahead_active_seg << std::endl;
    //std::cout << "farthest behind" << std::endl;
    //std::cout << farthest_behind_active_seg << std::endl;
    /*
    glm::vec3 eye = m_gameobject->getGameWorld()->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->getEye();
    if (eye.z > (farthest_ahead_active_seg - 2) * SEGMENT_LENGTH) {
        farthest_ahead_active_seg++;
        std::shared_ptr<MapSegment> newseg = MapGenerator::createMap(farthest_ahead_active_seg+1);
        enqueueDungeonChunksFromMapSegment(newseg);
        std::cout << "added new segment" << std::endl;
        std::cout << farthest_ahead_active_seg << std::endl;
        map_segments.push_back(newseg);
    }
    if (eye.z > (farthest_behind_active_seg + 2) * SEGMENT_LENGTH) {
        // get rid of segment
        m_gameobject->getGameWorld()->getSystem<ChunkStreamingSystem>()->
                destroyChunksBehindZValue(farthest_behind_active_seg * SEGMENT_LENGTH);
        std::cout << "removed old segment" << std::endl;
        std::cout << farthest_behind_active_seg << std::endl;
        farthest_behind_active_seg++;
    }
    if (eye.z < (farthest_behind_active_seg + 2) * SEGMENT_LENGTH && farthest_behind_active_seg > 2) {
        // add back segment
        farthest_behind_active_seg--;
        std::shared_ptr<MapSegment> newseg = MapGenerator::createMap(farthest_behind_active_seg+1);
        std::cout << "added back old segment" << std::endl;
        std::cout << farthest_behind_active_seg << std::endl;
        enqueueDungeonChunksFromMapSegment(newseg);
    }
    if (eye.z < (farthest_ahead_active_seg - 2) * SEGMENT_LENGTH && farthest_ahead_active_seg > 3) {
        // get rid of segment far ahead
        //std::cout << "got rid of far ahead segment" << std::endl;
        //std::cout << farthest_behind_active_seg << std::endl;
        //m_gameobject->getGameWorld()->getSystem<ChunkStreamingSystem>()->
                //destroyChunksBeyondZValue(farthest_ahead_active_seg * SEGMENT_LENGTH);
        //farthest_ahead_active_seg--;
    }
    */
    glm::vec3 eye = m_gameobject->getGameWorld()->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->getEye();
    if (eye.z > (farthest_ahead_active_seg - 2) * SEGMENT_LENGTH) {
        farthest_ahead_active_seg++;
        std::shared_ptr<MapSegment> newseg = MapGenerator::createMap(farthest_ahead_active_seg+1);
        enqueueDungeonChunksFromMapSegment(newseg);
        std::cout << "added new segment" << std::endl;
        std::cout << farthest_ahead_active_seg << std::endl;
        map_segments.push_back(newseg);
        m_gameobject->getGameWorld()->getSystem<ChunkStreamingSystem>()->
                destroyChunksBehindZValue(farthest_behind_active_seg * SEGMENT_LENGTH);
        std::cout << "removed old segment" << std::endl;
        std::cout << farthest_behind_active_seg << std::endl;
        farthest_behind_active_seg++;
    } else if ((eye.z < (farthest_ahead_active_seg - 2) * SEGMENT_LENGTH) && farthest_ahead_active_seg > 2) {
        /*
        // add back segment
        farthest_behind_active_seg--;
        std::shared_ptr<MapSegment> newseg = MapGenerator::createMap(farthest_behind_active_seg+1);
        std::cout << "added back old segment" << std::endl;
        std::cout << farthest_behind_active_seg << std::endl;
        enqueueDungeonChunksFromMapSegment(newseg);
        //m_gameobject->getGameWorld()->getSystem<ChunkStreamingSystem>()->
                //destroyChunksBeyondZValue(farthest_ahead_active_seg * SEGMENT_LENGTH);
        farthest_ahead_active_seg--;
        */
    }
}
