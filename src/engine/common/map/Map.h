#ifndef MAP_H
#define MAP_H

#include "src/engine/util/CommonIncludes.h"
#include <vector>
#include <random>

enum MapElement {OPEN, WALL, BLANK};

struct RoomInfo {
    int rowstart;
    int rowend;
    int colstart;
    int colend;
};

class Map {

public:
    Map(int seed);
    ~Map();

    void createMap(int seed);
    RoomInfo spacePartition(int depth, int colstart, int colend, int rowstart, int rowend);
    void printMap();
    void cleanUpMap();
    bool checkValidCoordinates(int row, int col);

private:
    std::vector<MapElement> map;
    const int MAX_DEPTH = 4;
    const float EARLY_STOP_PROB = .2f;
    const int MAP_WIDTH = 50;
    const int MAP_HEIGHT = 50;
    const int MIN_LEAF_WIDTH = 5;
    const int MIN_LEAF_HEIGHT = 5;
    const int MIN_ROOM_HEIGHT = 2;
    const int MIN_ROOM_WIDTH = 2;
};

#endif // MAP_H
