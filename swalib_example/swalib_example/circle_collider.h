#pragma once

#include "component.h"
#include "entity.h"
#include <vector>

struct CircleCollider : public Component {
  float radius = 0.f;
  virtual void Slot() override {}

  // Since it is a requirement that the components
  // process their own data, this have to be here
  bool IsColliding(std::vector<Entity *> *balls);
};
