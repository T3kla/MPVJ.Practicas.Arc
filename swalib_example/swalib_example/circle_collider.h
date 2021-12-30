#pragma once

#include "component.h"
#include "entity.h"

struct CircleCollider : public Component {
  float radius = 0.f;
  virtual void Slot() override {}

  bool IsColliding(std::vector<Entity> *balls);
};
