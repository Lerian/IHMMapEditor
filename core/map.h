#ifndef MAP_H
#define MAP_H

#include "floor.h"
#include <vector>

class Map
{
    std::vector<Floor> floors;

public:
    Map();

    void addFloor(Floor f);
};

#endif // MAP_H
