#pragma once

#include "entity_manager.h"
#include <set>

class System {
public:
  std::set<EntID> entities;
};
