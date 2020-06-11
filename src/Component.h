#pragma once

#include "Entity.h"

class Component {
public:
    virtual ~Component() {};
    
    void setEntity(Entity* e) { this->entity = e; };
    
    Entity* getEntity() { return entity; };

protected:
    Entity* entity;
};