#pragma once

#include "sol/sol.hpp"

#include "Entity.h"
#include "World.h"

class Level {
public:
    Level(World* wrld) : world(wrld) {}
    void generateMap(sol::table tiles);
private:
    World* world;
    Entity* map[128][128];
};