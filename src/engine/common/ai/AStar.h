#ifndef ASTAR_H
#define ASTAR_H

#include "src/engine/common/map/MapGenerator.h"
#include <map>
#include <set>

struct AStarState {
    int x;
    int z;
    float fcost;
    float gcost;
};

struct StateComparator {
    bool operator()(const std::shared_ptr<AStarState> s1, const std::shared_ptr<AStarState> s2) {
        return s1->fcost < s2->fcost;
    }
};

class AStar
{
public:
    AStar(std::shared_ptr<MapSegment> segment);
    ~AStar();
    std::vector<std::pair<int, int>> AStarAlgorithm(std::shared_ptr<AStarState> start, std::shared_ptr<AStarState> goal);
    std::vector<std::pair<int, int>> reconstructPath(std::pair<int, int> current,
            std::map<std::pair<int, int>, std::pair<int, int>> &came_from);
    std::vector<std::pair<int, int>> getNeighbors(std::shared_ptr<AStarState> node);

private:
    std::shared_ptr<MapSegment> m_segment;
};

#endif // ASTAR_H
