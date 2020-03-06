#include "DungeonApproachAction.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"

DungeonApproachAction::DungeonApproachAction(Component *component, std::shared_ptr<MapSegment> segment, float size) :
    Action(component),
    m_seg(segment)
{
    m_size = size;
    curr_step = 0;
    m_counter = 0;
    current_direction = glm::vec3(0,0,0);
    m_astar = std::make_shared<AStar>(segment);
}

DungeonApproachAction::~DungeonApproachAction()
{

}

void DungeonApproachAction::reset() {

}

Status DungeonApproachAction::update(float seconds) {
    m_counter += seconds;
    glm::vec3 player_pos = m_component->getGameObject()->getGameWorld()->
                           getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
    glm::vec3 enemy_pos = m_component->getGameObject()->getComponent<TransformComponent>()->getPos();
    if (m_counter > UPDATE_TIME) {
        m_counter = 0;
        int start_x = int((enemy_pos.x + m_size / 2.0f) / m_size);
        int start_z = int((enemy_pos.z + m_size / 2.0f) / m_size - m_seg->info.segment_num * MapGenerator::MAP_WIDTH);
        int goal_x = int((player_pos.x + m_size / 2.0f) / m_size);
        int goal_z = int((player_pos.z + m_size / 2.0f) / m_size - m_seg->info.segment_num * MapGenerator::MAP_WIDTH);
        std::shared_ptr<AStarState> start = std::make_shared<AStarState>();
        start->x = start_x;
        start->z = start_z;
        std::shared_ptr<AStarState> goal = std::make_shared<AStarState>();
        goal->x = goal_x;
        goal->z = goal_z;
        if (start_x < 0 || start_z < 0) {
            std::cout << "stop" << std::endl;
        }

        curr_path = m_astar->aStarAlgorithm(start, goal);
        curr_step = 0;
        std::cout << "mapped path" << std::endl;
    }

    if (curr_step + 1 < curr_path.size()) {
        float x_next = curr_path[curr_step + 1].first * m_size;
        float z_next = (curr_path[curr_step + 1].second + m_seg->info.segment_num * MapGenerator::MAP_WIDTH) * m_size;
        if (std::abs(x_next - enemy_pos.x) > 0 || std::abs(z_next - enemy_pos.z) > 0) {
            current_direction = glm::normalize(glm::vec3(x_next - enemy_pos.x, 0, z_next - enemy_pos.z));
        }
        m_component->getGameObject()->getComponent<TransformComponent>()->translate(ENEMY_SPEED * current_direction);
        m_component->getGameObject()->getComponent<TransformComponent>()->
                setYaw(std::atan2(current_direction.x, current_direction.z) - M_PI / 2.0f);
        if (glm::any(glm::isnan(m_component->getGameObject()->getComponent<TransformComponent>()->getPos()))) {
            std::cout << "stop" << std::endl;
        }
        if (glm::length(glm::vec3(x_next - enemy_pos.x, 0, z_next - enemy_pos.z)) < EPSILON) {
            curr_step++;
            std::cout << "moved step" << std::endl;
        }
    }

    return RUNNING;
}
