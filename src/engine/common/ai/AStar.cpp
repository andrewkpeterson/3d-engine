#include "AStar.h"

AStar::AStar(std::shared_ptr<MapSegment> segment) :
    m_segment(segment)
{

}

AStar::~AStar()
{

}

std::vector<std::pair<int, int>> AStar::aStarAlgorithm(std::shared_ptr<AStarState> start, std::shared_ptr<AStarState> goal) {
    std::set<std::shared_ptr<AStarState>, StateComparator> open_set;
    std::map<std::pair<int, int>, std::shared_ptr<AStarState>> pair2state;
    if (m_segment->data[(goal->x) * MapGenerator::MAP_WIDTH + goal->z] == MapElement::WALL ||
        m_segment->data[(goal->x) * MapGenerator::MAP_WIDTH + goal->z] == MapElement::BLANK) {
        std::cout << "enemy thinks player is inside wall" << std::endl;
    }
    if (m_segment->data[(start->x) * MapGenerator::MAP_WIDTH + start->z] == MapElement::WALL ||
        m_segment->data[(start->x) * MapGenerator::MAP_WIDTH + start->z] == MapElement::BLANK) {
        std::cout << "enemy thinks it is inside wall" << std::endl;
    }
    start->gcost = 0.0f;
    start->fcost = float(std::sqrt(std::pow(start->x - goal->x, 2) + std::pow(start->z - goal->z, 2)));

    open_set.insert(start);
    pair2state[std::pair<int, int>(start->x, start->z)] = start;
    std::map<std::pair<int, int>, std::pair<int, int>> came_from;

    while (open_set.size() > 0) {
        std::shared_ptr<AStarState> current = *open_set.begin();
        if (current->x == goal->x && current->z == goal->z) {
            return reconstructPath(std::pair<int, int>(current->x, current->z), came_from, start);
        }

        int prev_size = open_set.size();
        open_set.erase(current);
        if (prev_size == open_set.size()) {
            std::cout << "something bad happened" << std::endl;
            return std::vector<std::pair<int, int>>({});
        }
        std::vector<std::pair<int, int>> neighbors = getNeighbors(current);
        for (int i = 0; i < neighbors.size(); i++) {
            std::pair<int, int> n_pair = neighbors[i];
            float tentative_gcost = current->gcost + 1;
            bool found_previously = pair2state.find(n_pair) != pair2state.end();
            std::shared_ptr<AStarState> n_ptr;
            if (found_previously) {
                n_ptr = pair2state[n_pair];
            } else {
                n_ptr = std::make_shared<AStarState>();
                n_ptr->x = n_pair.first;
                n_ptr->z = n_pair.second;
                pair2state[n_pair] = n_ptr;
            }
            if (!found_previously || tentative_gcost < n_ptr->gcost) {
                came_from[std::pair<int, int>(n_ptr->x, n_ptr->z)] = std::pair<int, int>(current->x, current->z);
                n_ptr->gcost = tentative_gcost;
                n_ptr->fcost = tentative_gcost + float(std::sqrt(std::pow(n_ptr->x - goal->x, 2) + std::pow(n_ptr->z - goal->z, 2)));
                auto check = open_set.find(n_ptr);
                auto end = open_set.end();
                if (check != end) {
                    open_set.erase(n_ptr);
                    open_set.insert(n_ptr);
                } else {
                    open_set.insert(n_ptr);
                }
            }
        }
    }


    // return failure
    return std::vector<std::pair<int, int>>({});
}

std::vector<std::pair<int, int>> AStar::getNeighbors(std::shared_ptr<AStarState> node) {
    std::vector<std::pair<int, int>> retvec;
    if (m_segment->data[(node->x + 1) * MapGenerator::MAP_WIDTH + node->z] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x + 1, node->z));
    }
    if (m_segment->data[(node->x - 1) * MapGenerator::MAP_WIDTH + node->z] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x - 1, node->z));
    }
    if (m_segment->data[(node->x) * MapGenerator::MAP_WIDTH + node->z + 1] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x, node->z + 1));
    }
    if (m_segment->data[(node->x) * MapGenerator::MAP_WIDTH + node->z - 1] == MapElement::OPEN) {
        retvec.push_back(std::pair<int, int>(node->x, node->z - 1));
    }

    return retvec;
}

std::vector<std::pair<int, int>> AStar::reconstructPath(std::pair<int, int> current,
                                                        std::map<std::pair<int, int>, std::pair<int, int>> &came_from,
                                                        std::shared_ptr<AStarState> start) {
    std::vector<std::pair<int, int>> path;
    auto it = came_from.begin();
    while (it != came_from.end() && !(start->x == current.first && start->z == current.second)) {
        path.insert(path.begin(), current);
        current = came_from[current];
        it++;
    }
    path.insert(path.begin(), current);

    return path;
}
