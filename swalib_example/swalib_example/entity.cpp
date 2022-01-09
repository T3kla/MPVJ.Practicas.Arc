#include "entity.h"

Entity::Entity() {}

Entity::~Entity() {}

void Entity::RemoveAllComponents() {
  for (auto &cmp : components)
    delete cmp.second;
  components.clear();
}

void Entity::Slot() {

  // This is bad because
  //    Random component slot execution order inside the entity
  //    Random entity slot execution order
  //
  // This WILL cause weird visual glitches due to the randomness
  // of the execution of the physic and rendering parts

  for (auto &cmp : components)
    ((Component *)cmp.second)->Slot();
}
