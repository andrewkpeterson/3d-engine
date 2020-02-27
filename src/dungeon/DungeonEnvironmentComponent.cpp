#include "DungeonEnvironmentComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/component/StaticAABCollisionComponent.h"
#include "src/engine/common/component/ChunkComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"

DungeonEnvironmentComponent::DungeonEnvironmentComponent(float size, std::string atlas) :
    m_size(size),
    curr_segment(0),
    atlas_name(atlas)
{

}

DungeonEnvironmentComponent::~DungeonEnvironmentComponent()
{

}

void DungeonEnvironmentComponent::enqueueDungeonChunksFromMapSegment(int seg_idx, std::shared_ptr<MapSegment> seg) {
    if (seg_idx >= map_segments.size()) {
        map_segments.push_back(seg);
    }

    // split up the segment into 10 by 10 chunks
    for (int row = 0; row < MapGenerator::MAP_HEIGHT; row+=DUNGEON_CHUNK_SIZE) {
        for (int col = 0; col < MapGenerator::MAP_WIDTH; col+=DUNGEON_CHUNK_SIZE) {
            std::shared_ptr<GameObject> new_chunk_object = std::make_shared<GameObject>();
            new_chunk_object->addComponent<ChunkComponent>(
                        std::make_shared<ChunkComponent>(std::bind(&DungeonEnvironmentComponent::buildChunk, this,
                                                                   seg_idx, row, col, std::placeholders::_1)));
            new_chunk_object->addComponent<ChunkDrawableComponent>(std::make_shared<ChunkDrawableComponent>(atlas_name));
            new_chunk_object->addComponent<StaticAABCollisionComponent>(
                        std::make_shared<StaticAABCollisionComponent>(false, false, std::vector<AAB>({})));
            m_gameobject->getGameWorld()->addGameObject(new_chunk_object);
            if (chunk_map.find(seg->info.segment_num) == chunk_map.end()) {
                chunk_map[seg->info.segment_num] = std::unordered_set<std::shared_ptr<ChunkComponent>>();
            }

            chunk_map[seg->info.segment_num].insert(new_chunk_object->getComponent<ChunkComponent>());
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

bool DungeonEnvironmentComponent::buildChunk(int seg_idx, int startrow, int startcol, ChunkComponent* chunk_comp) {
    std::shared_ptr<MapSegment> seg = map_segments[seg_idx];
    std::vector<float> vert_data;
    std::vector<AAB> bounding_boxes;
    glm::vec3 pos = glm::vec3(startrow, 0, startcol + (seg->info.segment_num)*MapGenerator::MAP_WIDTH) * m_size;
    for (int row = startrow; row < startrow + DUNGEON_CHUNK_SIZE; row++) {
        for (int col = startcol; col < startcol + DUNGEON_CHUNK_SIZE; col++) {
            if (seg->data[row * MapGenerator::MAP_WIDTH + col] == WALL) {
                // make a cube with the appropriate texture
                bounding_boxes.push_back(
                            DungeonEnvironmentData::fillVectorWithWallData(vert_data, row,
                                                                           col + (seg->info.segment_num)*MapGenerator::MAP_WIDTH,
                                                                           4*.0625, 5*.0625, 13*.0625, 14*.0625));
            } else if (seg->data[row * MapGenerator::MAP_WIDTH + col] == OPEN) {
                //make a ceiling and floor with appropriate textures
                DungeonEnvironmentData::fillVectorWithCeilingData(vert_data, row, col + (seg->info.segment_num)*MapGenerator::MAP_WIDTH,
                                                                  0, .0625, 1-.0625, 1);
                DungeonEnvironmentData::fillVectorWithFloorData(vert_data, row, col + (seg->info.segment_num)*MapGenerator::MAP_WIDTH,
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

void DungeonEnvironmentComponent::addSegment(std::shared_ptr<MapSegment> seg) {

}

void DungeonEnvironmentComponent::tick(float seconds) {
    glm::vec3 eye = m_gameobject->getGameWorld()->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->getEye();
    curr_segment = int(std::floor(float(eye.z) / float(m_size* MapGenerator::MAP_WIDTH)));
    auto it = chunk_map.begin();
    int max_seg = 0;
    int min_seg = INT_MAX;
    while (it != chunk_map.end()) {
        if (it->first > curr_segment + 2) { // segment is too far ahead
            std::cout << "removed segment" << std::endl;
            std::cout << it->first << std::endl;
            auto chunk_it = chunk_map[it->first].begin();
            while (chunk_it != chunk_map[it->first].end()) {
                m_gameobject->getGameWorld()->markGameObjectForDeletion(chunk_it->get()->getGameObject()->getID());
                chunk_it++;
            }
        } else if (it->first < curr_segment - 2) { // segment is too far behind
            std::cout << "removed segment" << std::endl;
            std::cout << it->first << std::endl;
            auto chunk_it = chunk_map[it->first].begin();
            while (chunk_it != chunk_map[it->first].end()) {
                std::string id = chunk_it->get()->getGameObject()->getID();
                m_gameobject->getGameWorld()->markGameObjectForDeletion(id);
                chunk_it++;
            }
        }
        if (it->first > max_seg) {
            max_seg = it->first;
        }
        if (it->first < min_seg) {
            min_seg = it->first;
        }
        it++;
    }
}
