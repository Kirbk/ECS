#pragma once
 
#include <string>

#include "sol/sol.hpp"

#include "Component.h"
#include "Entity.h"
 
class NPCComponent : public Component {
public:
    NPCComponent(Entity* e, sol::table& componentTable);
 
    void setPhrase(const std::string& phrase) {
        this->phrase = phrase;
    }
 
    std::string getPhrase() const {
        return phrase;
    }
private:
    std::string phrase;
};