#include <iostream>

#include "lua.hpp"

#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(Entity* e, sol::table& componentTable) {
    filename = componentTable["filename"];
    tex.loadFromFile(filename);
    sprite.setTexture(tex);

    if (componentTable["scale"]) {
        scale = sf::Vector2f(componentTable["scale"]["x"], componentTable["scale"]["y"]);
        std::cout << "ASDFASDFASDFASDFASFASDFASFASDFASFD\n";
    }
}