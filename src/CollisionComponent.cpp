#include <iostream>

#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Entity* entity, sol::table& componentTable) {
    this->setEntity(entity);
    this->setBoundingBox(componentTable["boundingBox"][1], componentTable["boundingBox"][2],
                         componentTable["boundingBox"][3], componentTable["boundingBox"][4]);
    collide = componentTable["collide"];
    componentTable.set("test", [this] () { this->_test(); });

    // componentTable.for_each([] (std::pair<sol::object, sol::object> key_value_pair) {
    //     std::cout << key_value_pair.first.as<std::string>() << std::endl;
    // });

    // Entity* e = this->getEntity();
    // std::cout << e << std::endl;
    // collide(e, e);
}

void CollisionComponent::_test() {
    std::cout << this->getEntity()->getType() << std::endl;
}