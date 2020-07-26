#include <iostream>

#include "lua.hpp"

#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(Entity* e, sol::table& ct) : componentTable(ct) {
    entity = e;
    filename = ct["filename"];
    tex.loadFromFile(filename);
    sprite.setTexture(tex);

    if (ct["scale"]) {
        scale = sf::Vector2f(ct["scale"]["x"], ct["scale"]["y"]);
        std::cout << "ASDFASDFASDFASDFASFASDFASFASDFASFD\n";
    }
}