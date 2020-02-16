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

struct MapInfo {
    int x;
    int y;
    int seed;
};

struct MapSegment {
    std::vector<MapElement> data;
    MapInfo info;
    MapInfo next;
};

class MapGenerator {

public:
    MapGenerator();
    ~MapGenerator();

    static std::shared_ptr<MapSegment> createMap(int seed);
    static void printMap(std::shared_ptr<MapSegment> map);

private:
    static void cleanUpMap(std::shared_ptr<MapSegment> map);
    static bool checkValidCoordinates(int row, int col);
    static void addExit();
    static RoomInfo spacePartition(std::shared_ptr<MapSegment> map, int depth, int colstart, int colend, int rowstart, int rowend);

    std::vector<MapElement> map;
    static const int MAX_DEPTH = 4;
    static const constexpr float EARLY_STOP_PROB = .2f;
    static const int MAP_WIDTH = 50;
    static const int MAP_HEIGHT = 50;
    static const int MIN_LEAF_WIDTH = 5;
    static const int MIN_LEAF_HEIGHT = 5;
    static const int MIN_ROOM_HEIGHT = 2;
    static const int MIN_ROOM_WIDTH = 2;
    static std::vector<MapInfo> map_info;
};

#endif // MAP_H
