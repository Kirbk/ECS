#pragma once
 
#include <string>

#include "sol/sol.hpp"
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "Entity.h"
 
class GraphicsComponent : public Component {
public:
    GraphicsComponent(Entity* e, sol::table& componentTable);
 
    void setFilename(const std::string& filename) {
        this->filename = filename;
        this->tex.loadFromFile(filename);
        this->sprite.setTexture(tex);
        this->sprite.setPosition(200.f, 200.f);
    }

    void setLocation(float x, float y) {
        location.x = x;
        location.y = y;
    }

    void setLocation(sf::Vector2f v) {
        location = v;
    }

    void setScale(float x, float y) {
        scale.x = x;
        scale.y = y;
    }

    void setScale(sf::Vector2f v) {
        scale = v;
    }

    sf::Texture getTexture() {
        return tex;
    }

    sf::Sprite* getSprite() {
        return &sprite;
    }
     
    std::string getFilename() const {
        return filename;
    }

    sf::Vector2f getLocation() {
        return location;
    }

    sf::Vector2f getScale() {
        return scale;
    }

    GraphicsComponent* clone() {
        GraphicsComponent* gc = new GraphicsComponent(entity, componentTable);
        gc->entity = entity;
        gc->componentTable = componentTable;
        gc->filename = filename;
        gc->tex = tex;
        gc->sprite = sprite;
        gc->location = location;
        gc->scale = scale;

        return gc;
    }
    
private:
    Entity* entity;
    sol::table& componentTable;
    std::string filename;
    sf::Texture tex;
    sf::Sprite sprite;
    sf::Vector2f location;
    sf::Vector2f scale;
};