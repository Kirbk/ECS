
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

void World::loadEntity(sol::object& et, const std::string& type, bool isTile) {
    sol::table eTree = et;

    //entityMap.insert(std::pair<std::string, Entity*>(e->getType(), e));
    entityMap.insert(std::pair<std::string, sol::object&>(type, et));
}

Entity* World::spawnEntity(std::string name, glm::vec2 position) {
    sol::table eTree = entityMap.find(name)->second;
    Entity* e = new Entity();

    e->setType(name);

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

    e->setPosition(position);

    addEntity(e);
    return e;
}

Entity* World::spawnEntity(std::string name, glm::vec2 position, glm::vec2 scale) {
    Entity* e = spawnEntity(name, position);
    GraphicsComponent* gc = e->get<GraphicsComponent>();
    if (gc)
        gc->getSprite()->setScale(scale.x, scale.y);

    return e;
}

void World::update() {
    // TODO: Spatial Partitioning

    for (Entity* e : entities) {
        e->update();
    }
}