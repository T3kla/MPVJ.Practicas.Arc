#pragma once

#include "component.h"

struct CircleCollider : public Component {
  float radius = 0.f;
  virtual void Slot() override{};
};
