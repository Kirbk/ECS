#pragma once
 
#include <map>
#include <string>
#include <typeindex>
 
#include "glm/vec2.hpp"

class Component;
 
class Entity {
public:
    ~Entity();
    void addComponent(std::type_index type, Component* c);
 
    template <typename T>
    T* get() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
     
    void setType(const std::string& type) {
        this->type = type;
    }
 
    std::string getType() const {
        return type;
    }

    void update();

    void setPosition(glm::vec2 pos) {
        this->position = pos;
    }

    glm::vec2 getPosition() {
        return this->position;
    }

    Entity* clone() {
        Entity* e = new Entity();
        e->type = this->type;
        for (auto const& it : components) {
            e->addComponent(it.first, it.second);
        }
        e->position = this->position;

        return e;
    }
private:
    std::string type;
    std::map<std::type_index, Component*> components;
    glm::vec2 position;
};