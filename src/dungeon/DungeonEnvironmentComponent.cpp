#include "DungeonEnvironmentComponent.h"
#include "src/engine/common/system/TickSystem.h"
#include "src/engine/common/component/StaticAABCollisionComponent.h"
#include "src/engine/common/component/DynamicAABCollisionComponent.h"
#include "src/engine/common/component/ChunkComponent.h"
#include "src/engine/common/component/PrimitiveDrawableComponent.h"
#include "src/engine/common/component/TransformComponent.h"
#include "src/engine/common/system/CameraSystem.h"
#include "src/engine/common/system/ChunkStreamingSystem.h"
#include "src/dungeon/DungeonEnemyAIComponent.h"

DungeonEnvironmentComponent::DungeonEnvironmentComponent(float size, std::string atlas) :
    m_size(size),
    curr_segment(0),
    atlas_name(atlas),
    farthest_ahead_segment(2),
    farthest_back_segment(0)
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
            if (chunk_map.find(seg_idx) == chunk_map.end()) {
                chunk_map[seg_idx] = std::unordered_set<std::shared_ptr<ChunkComponent>>();
            }

            chunk_map[seg_idx].insert(new_chunk_object->getComponent<ChunkComponent>());
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
    updateEnvironment(seconds);
}

void DungeonEnvironmentComponent::addEnemies(int segnum) {
    enemy_map[segnum] = std::unordered_set<std::shared_ptr<GameObject>>();
    for (int i = 0; i < ENEMIES_PER_SEG; i++) {
        std::shared_ptr<GameObject> cube = std::make_shared<GameObject>();
        enemy_map[segnum].insert(cube);
        cube->addComponent<DynamicAABCollisionComponent>(std::make_shared<DynamicAABCollisionComponent>(false, true, glm::vec3(1,1,1)));
        cube->addComponent<DungeonEnemyAIComponent>(std::make_shared<DungeonEnemyAIComponent>(map_segments[segnum]));

        bool found = false;
        while (!found) {
            int col = std::rand() % MapGenerator::MAP_WIDTH;
            int row = std::rand() % MapGenerator::MAP_HEIGHT;
            if (map_segments[segnum]->data[row * MapGenerator::MAP_WIDTH + col] == OPEN) {
                found = true;
                float x = row * m_size;
                float z = (col + segnum * MapGenerator::MAP_WIDTH) * m_size;
                cube->getComponent<TransformComponent>()->setPos(glm::vec3(x, 1.0, z));
                cube->getComponent<TransformComponent>()->setScale(2.0f);
            }
        }

        cube->getComponent<TransformComponent>()->setScale(2.0f);
        Material cube_mat;
        cube_mat.color = glm::vec3(.8,.4,.3);
        cube->addComponent<PrimitiveDrawableComponent>(std::make_shared<PrimitiveDrawableComponent>("cube", "cube_mat", cube_mat));
        m_gameobject->getGameWorld() ->addGameObject(cube);
    }
}

void DungeonEnvironmentComponent::removeEnemies(int segnum) {
    auto it = enemy_map[segnum].begin();
    while (it != enemy_map[segnum].end()) {
        std::shared_ptr<GameObject> g = *it;
        m_gameobject->getGameWorld()->markGameObjectForDeletion(g->getID());
        it++;
    }
    enemy_map.erase(segnum);
}

void DungeonEnvironmentComponent::updateEnvironment(float seconds) {
    glm::vec3 eye = m_gameobject->getGameWorld()->getSystem<CameraSystem>()->getCurrentMainCameraComponent()->getCamera()->getEye();
    int new_segment = int(std::floor(float(eye.z) / float(m_size* MapGenerator::MAP_WIDTH)));
    if (new_segment > curr_segment) {
        // add new segment ahead and remove segment behind
        int segment_ahead = curr_segment + 2;
        if (segment_ahead >= map_segments.size()) {
            std::cout << "add segment ahead" << std::endl;
            std::cout << segment_ahead << std::endl;
            std::shared_ptr<MapSegment> seg = MapGenerator::createMap(segment_ahead);
            enqueueDungeonChunksFromMapSegment(segment_ahead, seg);
            addEnemies(segment_ahead);
        } else {
            enqueueDungeonChunksFromMapSegment(segment_ahead, map_segments[segment_ahead]);
            addEnemies(segment_ahead);
        }

        int segment_behind = curr_segment - 2;
        if (segment_behind >= 0) {
            std::cout << "remove segment behind" << std::endl;
            std::cout << segment_behind << std::endl;
            auto chunk_it = chunk_map[segment_behind].begin();
            while (chunk_it != chunk_map[segment_behind].end()) {
                m_gameobject->getGameWorld()->markGameObjectForDeletion(chunk_it->get()->getGameObject()->getID());
                chunk_it++;
            }
            chunk_map.erase(segment_behind);
            removeEnemies(segment_behind);
        }

    } else if (new_segment < curr_segment) {
        // add new segment behind and remove segment ahead
        int segment_ahead = curr_segment + 1;
        std::cout << "remove segment ahead" << std::endl;
        std::cout << segment_ahead << std::endl;
        if (segment_ahead > 2) {
            auto chunk_it = chunk_map[segment_ahead].begin();
            while (chunk_it != chunk_map[segment_ahead].end()) {
                m_gameobject->getGameWorld()->markGameObjectForDeletion(chunk_it->get()->getGameObject()->getID());
                chunk_it++;
            }
            chunk_map.erase(segment_ahead);
            removeEnemies(segment_ahead);
        }

        int segment_behind = curr_segment - 3;
        if (segment_behind >= 0) {
            std::cout << "add segment behind" << std::endl;
            std::cout << segment_behind << std::endl;
            enqueueDungeonChunksFromMapSegment(segment_behind, map_segments[segment_behind]);
            addEnemies(segment_behind);
        }
    }

    curr_segment = new_segment;
}
