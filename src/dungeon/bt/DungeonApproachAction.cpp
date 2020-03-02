#include "DungeonApproachAction.h"
#include "src/engine/common/GameObject.h"
#include "src/engine/common/GameWorld.h"
#include "src/engine/common/component/TransformComponent.h"

DungeonApproachAction::DungeonApproachAction(Component *component, std::shared_ptr<MapSegment> segment, float size) :
    Action(component),
    m_seg(segment),
    m_astar(std::make_shared<AStar>(segment)),
    m_size(size)
{

}

DungeonApproachAction::~DungeonApproachAction()
{

}

void DungeonApproachAction::reset() {

}

Status DungeonApproachAction::update(float seconds) {
    glm::vec3 player_pos = m_component->getGameObject()->getGameWorld()->
                           getGameObjectByID("player")->getComponent<TransformComponent>()->getPos();
    glm::vec3 enemy_pos = m_component->getGameObject()->getComponent<TransformComponent>()->getPos();
    int start_x = int(enemy_pos.x / m_size);
    int start_z = int(enemy_pos.z / m_size - m_seg->info.segment_num * MapGenerator::MAP_WIDTH);
    int goal_x = int(player_pos.x / m_size);
    int goal_z = int(player_pos.z / m_size - m_seg->info.segment_num * MapGenerator::MAP_WIDTH);
    std::shared_ptr<AStarState> start = std::make_shared<AStarState>();
    start->x = start_x;
    start->z = start_z;
    std::shared_ptr<AStarState> goal = std::make_shared<AStarState>();
    goal->x = goal_x;
    goal->z = goal_z;

    std::vector<std::pair<int, int>> path = m_astar->aStarAlgorithm(start, goal);
    if (path.size() > 1) {
        // get the right index!!!!!!
        float x_next = path[1].first * m_size;
        float z_next = (path[1].second + m_seg->info.segment_num * MapGenerator::MAP_WIDTH) * m_size;
        std::cout << x_next << std::endl;
        std::cout << z_next << std::endl;
        glm::vec3 translate = glm::normalize(glm::vec3(x_next - enemy_pos.x, 0, z_next - enemy_pos.z));
        //if (glm::length(glm::vec2(x_next - enemy_pos.x, z_next - enemy_pos.z))) {
            m_component->getGameObject()->getComponent<TransformComponent>()->translate(ENEMY_SPEED * translate);
        //}
    }

    return RUNNING;
}
