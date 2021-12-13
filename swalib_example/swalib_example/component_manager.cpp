#include "component_manager.h"

void ComponentMan::EntityDestroyed(EntID id) const {
  for (auto const &pair : name_juggler) {
    auto &cmp = pair.second;
    cmp->EntityDestroyed(id);
  }
}
