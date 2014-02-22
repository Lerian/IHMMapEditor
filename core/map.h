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
    int getFloorNumber() {return floors.size();}
    Floor getFloorAt(int i) {return floors.at(i);}
};

#endif // MAP_H
