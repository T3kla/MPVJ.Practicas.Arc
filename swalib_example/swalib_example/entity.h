#pragma once

#include "entity_manager.h"

class Entity {
protected:
  EntID id = 0;

public:
  virtual EntID GetEntID() const { return id; }
  virtual void SetEntID(const EntID &id) { this->id = id; }
};
