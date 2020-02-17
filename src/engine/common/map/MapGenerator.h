#ifndef MAP_H
#define MAP_H

#include "src/engine/util/CommonIncludes.h"
#include <vector>
#include <random>
#include <memory>

enum MapElement {OPEN, WALL, BLANK};

struct RoomInfo {
    int rowstart;
    int rowend;
    int colstart;
    int colend;
};

struct SegmentInfo {
    int segment_num;
    int exit_row;
    int seed;
};

struct MapSegment {
    std::vector<MapElement> data;
    SegmentInfo info;
};

class MapGenerator {

public:
    MapGenerator();
    ~MapGenerator();

    static std::shared_ptr<MapSegment> createMap(int seed);
    static void printMap(std::shared_ptr<MapSegment> map);

    static const int MAP_WIDTH = 30;
    static const int MAP_HEIGHT = 30;

private:
    static void cleanUpMap(std::shared_ptr<MapSegment> map);
    static bool checkValidCoordinates(int row, int col);
    static void addSegmentExit(std::shared_ptr<MapSegment> map);
    static void addSegmentEntrance(std::shared_ptr<MapSegment> map);
    static RoomInfo spacePartition(std::shared_ptr<MapSegment> map, int depth, int colstart, int colend, int rowstart, int rowend);

    std::vector<MapElement> map;
    static const int MAX_DEPTH = 3;
    static const int initial_seed = 506;
    static const constexpr float EARLY_STOP_PROB = .2f;
    static const int MIN_LEAF_WIDTH = 5;
    static const int MIN_LEAF_HEIGHT = 5;
    static const int MIN_ROOM_HEIGHT = 2;
    static const int MIN_ROOM_WIDTH = 2;
    static std::vector<SegmentInfo> segment_info; // contains all the map info for maps that have been created by the Map Generator
    static int next_segment_num;
};

#endif // MAP_H
