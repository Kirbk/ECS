#pragma once

#include "sol/sol.hpp"

#include "Component.h"
#include "Entity.h"
#include "glm/vec4.hpp"
 
class CollisionComponent : public Component {
public:
    CollisionComponent(Entity* entity, sol::table& componentTable);

    void setBoundingBox(glm::vec4 box) {
        _boundingBox = box;
    }

    void setBoundingBox(float x, float y, float z, float w) {
        _boundingBox = glm::vec4(x, y, z, w);
    }

    glm::vec4& getBoundingBox() {
        return _boundingBox;
    }

    sol::function collide;

private:
    void _test();

    glm::vec4 _boundingBox;
};