#include "entity.h"

Entity::Entity() {}

Entity::~Entity() {
  for (auto &cmp : components) 
    delete cmp.second;
  components.clear();
}

void Entity::Slot() {}
