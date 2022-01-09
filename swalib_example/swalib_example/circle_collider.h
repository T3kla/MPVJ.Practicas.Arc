#pragma once

#include "component.h"
#include "entity.h"
#include "transform.h"
#include <vector>

struct CircleCollider : public Component {
  float radius = 0.f;
  virtual void Slot() override {}

  static bool AreColliding(const Transform &aTF, const CircleCollider &aCC,
                           const Transform &bTF, const CircleCollider &bCC);

  static bool AnyOverlap(const Transform &tf, const CircleCollider &cc,
                         std::vector<Entity *> balls);
};
