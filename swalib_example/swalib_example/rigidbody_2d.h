#pragma once

#include "vec.h"

struct Rigidbody2D {
  float mass = 1.f;
  Vec2 velocity = {0.f, 0.f};
};
