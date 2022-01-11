#include "entity.h"

Entity::Entity() {}

Entity::~Entity() {}

void Entity::SendMessageNoWin(Msg *msg) {
  for (auto &cmp : components)
    ((Component *)cmp.second)->ReceiveMessage(msg);
}

void Entity::RemoveAllComponents() {
  for (auto &cmp : components)
    delete cmp.second;
  components.clear();
}

void Entity::Slot() {
  for (auto &cmp : components)
    ((Component *)cmp.second)->Slot();
}
