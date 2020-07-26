#include "Level.h"

#include "GraphicsComponent.h"

void Level::generateMap(sol::table& tiles) {
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            map[i][j] = this->world->spawnEntity("tile_water", glm::vec2(i * 16, j * 16), glm::vec2(2, 2));
        }
    }
}
