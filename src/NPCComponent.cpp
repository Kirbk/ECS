#include <iostream>
#include "NPCComponent.h"
#include "lua.hpp"

 
NPCComponent::NPCComponent(Entity* e, sol::table& NpcTable) {
    phrase = NpcTable["phrase"];
}