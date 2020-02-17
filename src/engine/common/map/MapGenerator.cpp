#include "MapGenerator.h"

int MapGenerator::next_segment_num = 0;
std::vector<SegmentInfo> MapGenerator::segment_info = {};

MapGenerator::MapGenerator() {

}

MapGenerator::~MapGenerator() {

}

std::shared_ptr<MapSegment> MapGenerator::createMap(int seed) {
    std::srand(seed);
    std::shared_ptr<MapSegment> map = std::make_shared<MapSegment>();
    map->info.seed = seed;
    map->info.segment_num = next_segment_num;
    next_segment_num++;
    map->data.reserve(MAP_WIDTH * MAP_HEIGHT);
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        map->data.push_back(WALL);
    }
    spacePartition(map, 0, 1, MAP_WIDTH-1, 1, MAP_HEIGHT-1);
    // choose the direction where the next segment will be added
    addSegmentExit(map);
    if (map->info.segment_num > 0) {
        addSegmentEntrance(map);
    }
    cleanUpMap(map);
    MapGenerator::segment_info.push_back(map->info);
    printMap(map);
    return map;
}

RoomInfo MapGenerator::spacePartition(std::shared_ptr<MapSegment> map, int depth, int colstart, int colend, int rowstart, int rowend) {
    float stop = float(std::rand()) / float(RAND_MAX);
    if (depth > MAX_DEPTH || (depth == 2 && stop < EARLY_STOP_PROB)) {
        // create leaf
        int max_height = rowend - rowstart;
        int min_height = (rowend - rowstart) / 2;
        int max_width =  colend - colstart;
        int min_width = (colend - colstart) / 2;
        int height = (std::rand() % (max_height - min_height)) + min_height;
        int width = (std::rand() % (max_width - min_width)) + min_width;
        int room_row_start = (std::rand() % (max_height - height)) + rowstart;
        int room_col_start = (std::rand() % (max_width - width)) + colstart;
        for (int row = 1; row < MAP_HEIGHT-1; row++) {
            for (int col = 1; col < MAP_WIDTH-1; col++) {
                if (row >= room_row_start && row < room_row_start + height) {
                    if (col >= room_col_start && col < room_col_start + width) {
                        map->data[row * MAP_WIDTH + col] = OPEN;
                    }
                }
            }
        }
        return RoomInfo({room_row_start, room_row_start + height, room_col_start, room_col_start + width});
    } else {
        if (depth % 2 == 0 && (rowend - rowstart) > MIN_LEAF_HEIGHT && (colend - colstart) > MIN_LEAF_WIDTH) {
            // split horizontally
            int split_start = 3*rowstart / 4 + rowend / 4;
            int split_end = 3*rowend / 4 + rowstart / 4;
            int split_row = (std::rand() % (split_end - split_start)) + split_start;
            RoomInfo top = spacePartition(map, depth + 1, colstart, colend, rowstart, split_row);
            RoomInfo bottom = spacePartition(map, depth + 1, colstart, colend, split_row, rowend);
            // connect the two child nodes
            // select column to connect the two child nodes
            int begincol = std::max(top.colstart, bottom.colstart);
            int endcol = std::min(top.colend, bottom.colend);
            int connection_col = (std::rand() % (endcol - begincol)) + begincol;
            int row_connection_start = top.rowstart;
            int row_connection_end = bottom.rowend;
            for (int row = 1; row < MAP_HEIGHT-1; row++) {
                for (int col = 1; col < MAP_WIDTH-1; col++) {
                    if (row >= row_connection_start && row < row_connection_end) {
                        if (col == connection_col) {
                            map->data[row * MAP_WIDTH + col] = OPEN;
                        }
                    }
                }
            }
            return RoomInfo({top.rowstart, bottom.rowend, begincol, endcol});
        } else if ((colend - colstart) > MIN_LEAF_WIDTH && (rowend - rowstart) > MIN_LEAF_HEIGHT) {
            // split vertically
            int split_start = 3*colstart / 4 + colend / 4;
            int split_end = 3*colend / 4 + colstart / 4;
            int split_col = (std::rand() % (split_end - split_start)) + split_start;
            RoomInfo left = spacePartition(map, depth + 1, colstart, split_col, rowstart, rowend);
            RoomInfo right = spacePartition(map, depth + 1, split_col, colend, rowstart, rowend);
            // connect the two child nodes
            // select row to connect the two child nodes
            int beginrow = std::max(left.rowstart, right.rowstart);
            int endrow = std::min(left.rowend, right.rowend);
            int connection_row = (std::rand() % (endrow - beginrow)) + beginrow;
            int col_connection_start = left.colstart;
            int col_connection_end = right.colend;
            for (int row = 1; row < MAP_HEIGHT-1; row++) {
                for (int col = 1; col < MAP_WIDTH-1; col++) {
                    if (col >= col_connection_start && col < col_connection_end) {
                        if (row == connection_row) {
                            map->data[row * MAP_WIDTH + col] = OPEN;
                        }
                    }
                }
            }
            return RoomInfo({beginrow, endrow, left.colstart, right.colend});
        }

        return RoomInfo({rowstart, rowend, colstart, colend});
    }
}

void MapGenerator::addSegmentEntrance(std::shared_ptr<MapSegment> map) {
    int entrance_row = segment_info[map->info.segment_num - 1].exit_row;
    int col = 0;
    while (map->data[entrance_row * MAP_WIDTH + col] != OPEN) {
        map->data[entrance_row * MAP_WIDTH + col] = OPEN;
        col++;
    }
}

void MapGenerator::addSegmentExit(std::shared_ptr<MapSegment> map) {
    /*
    for (int row = 1; row < MAP_WIDTH-1; row++) {
        for (int col = MAP_HEIGHT-2; col >= 1; col--) {
            if (map->data[row * MAP_WIDTH + col] == OPEN) {
                int exit_row = row;
                int exit_col = col;
                for (int c = exit_col; c < MAP_WIDTH; c++) {
                    map->data[exit_row * MAP_WIDTH + c] = OPEN;
                }
                map->info.exit_row = exit_row;
                return;
            }
        }
    }*/
    int exit_row = std::rand() % (MAP_WIDTH - 2) + 1;
    int col = MAP_WIDTH - 1;
    while(map->data[exit_row * MAP_WIDTH + col] != OPEN) {
            map->data[exit_row * MAP_WIDTH + col] = OPEN;
            col--;
    }
    map->info.exit_row = exit_row;
}

void MapGenerator::cleanUpMap(std::shared_ptr<MapSegment> map) {
    std::vector<bool> remove;
    remove.reserve(MAP_WIDTH * MAP_HEIGHT);
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        remove.push_back(false);
    }
    for (int row = 0; row < MAP_WIDTH; row++) {
        for (int col = 0; col < MAP_HEIGHT; col++) {
            bool found_open  = 0;
            if (checkValidCoordinates(row + 1, col) && map->data[(row+1)*MAP_WIDTH+col] == OPEN) {
                found_open = true;
            }
            if (checkValidCoordinates(row, col + 1) && map->data[row*MAP_WIDTH+col+1] == OPEN) {
                found_open = true;
            }
            if (checkValidCoordinates(row - 1, col) && map->data[(row-1)*MAP_WIDTH+col] == OPEN) {
                found_open = true;
            }
            if (checkValidCoordinates(row, col - 1) && map->data[row*MAP_WIDTH+col-1] == OPEN) {
                found_open = true;
            }
            if (!found_open) {
                remove[row * MAP_WIDTH + col] = true;
            }
        }
    }
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        if (remove[i]) {
            map->data[i] = BLANK;
        }
    }
}

bool MapGenerator::checkValidCoordinates(int row, int col) {
    return row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH;
}

void MapGenerator::printMap(std::shared_ptr<MapSegment> map) {
    std::cout << "\n\n\nSTART MAP\n\n\n" << std::endl;
    for (int row = 0; row < MAP_WIDTH; row++) {
        for (int col = 0; col < MAP_HEIGHT; col++) {
            if (map->data[row * MAP_WIDTH + col] == OPEN) {
                std::cout << " ";
            } else if (map->data[row * MAP_WIDTH + col] == WALL) {
                std::cout << "=";
            } else if (map->data[row * MAP_WIDTH + col] == BLANK) {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n\nEND MAP\n\n\n" << std::endl;
}
