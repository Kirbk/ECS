#include "Entity.h"
#include "Component.h"
#include "GraphicsComponent.h"

Entity::~Entity() {
    for (auto& c : components) {
        delete c.second;
    }
}
 
void Entity::addComponent(std::type_index type, Component* c) {
    components[type] = c;
}

glm::vec2 Entity::getPosition() {
    GraphicsComponent* gc = this->get<GraphicsComponent>();
    if (gc)
        return glm::vec2(gc->getSprite()->getPosition().x, gc->getSprite()->getPosition().y);
    else
        return glm::vec2(0, 0);
}

void Entity::setPosition(glm::vec2 pos) {
    GraphicsComponent* gc = this->get<GraphicsComponent>();
    gc->getSprite()->setPosition(sf::Vector2(pos.x, pos.y));
}

void Entity::update() {
    
}