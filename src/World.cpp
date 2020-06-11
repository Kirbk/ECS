
#include "World.h"
#include "GraphicsComponent.h"
#include "NPCComponent.h"
#include "CollisionComponent.h"

World::World() {
    
}

template <typename T>
void addComponent(Entity* e, sol::table& componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(e, componentTable));
}

Entity* World::loadEntity(sol::table eTree, const std::string& type) {
    Entity* e = new Entity();

    if (eTree["name"]) {
        e->setType(eTree["name"]);
        eTree["name"] = nullptr;
    }
    else {
        e->setType(type);
    }

    for (const auto& key_value_pair : eTree) {
        sol::object key = key_value_pair.first;
        sol::object value = key_value_pair.second;
        if (key.as<std::string>() == "GraphicsComponent") {
            sol::table gcTree = eTree["GraphicsComponent"];
            addComponent<GraphicsComponent>(e, gcTree);
        }
        else if (key.as<std::string>() == "NPCComponent") {
            sol::table npcTree = eTree["NPCComponent"];
            addComponent<NPCComponent>(e, npcTree);
        }
        else if (key.as<std::string>() == "CollisionComponent") {
            sol::table colTree = eTree["CollisionComponent"];
            addComponent<CollisionComponent>(e, colTree);
        }
        std::cout << "Added " << key.as<std::string>() << " to " << e->getType() << std::endl;
    }

    entityMap.insert(std::pair<std::string, Entity*>(e->getType(), e));
    return e;
}

void World::generateMap(sol::table& componentTable) {
    for(int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            
        }
    }
}

void World::spawnEntity(std::string name, glm::vec2 position) {
    Entity* e = entityMap.find(name)->second->clone();
    e->setPosition(position);

    addEntity(e);
}

void World::update() {
    // TODO: Spatial Partitioning

    for (Entity* e : entities) {
        e->update();
    }
}