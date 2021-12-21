#pragma once

#include "component.h"
#include "vec.h"

struct Transform : public Component {
  Vec2 position = {0.f, 0.f};
  virtual void Slot() override {}
};
