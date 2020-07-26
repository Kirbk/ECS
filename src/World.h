
#pragma once

#include <vector>

#include "glm/vec2.hpp"

#include "Entity.h"

#include "sol/sol.hpp"

class World {
public:
    World();
    ~World() {};

    void update();

    Entity* loadEntity(sol::table eTree, const std::string& type);

    void addEntity(Entity* e) {
        entities.push_back(e);
    }

    std::vector<Entity*> getEntities() {
        return entities;
    }

    Entity* spawnEntity(std::string name, glm::vec2 position, glm::vec2 scale);
    Entity* spawnEntity(std::string name, glm::vec2 position);

    void printEntityMap () {
        for (auto const& pair : entityMap) {
            std::cout << pair.first << std::endl;
            
        }
    }

private:
    std::vector<Entity*> entities;
    std::map<std::string, Entity*> entityMap;
};