
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

Entity* World::spawnEntity(std::string name, glm::vec2 position) {
    Entity* e = entityMap.find(name)->second->clone();
    e->setPosition(position);
    GraphicsComponent* gc = e->get<GraphicsComponent>();

    addEntity(e);
    return e;
}

Entity* World::spawnEntity(std::string name, glm::vec2 position, glm::vec2 scale) {
    Entity* e = entityMap.find(name)->second->clone();
    e->setPosition(position);
    GraphicsComponent* gc = e->get<GraphicsComponent>();
    if (gc)
        gc->getSprite()->setScale(scale.x, scale.y);

    addEntity(e);
    return e;
}

void World::update() {
    // TODO: Spatial Partitioning

    for (Entity* e : entities) {
        e->update();
    }
}