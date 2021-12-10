#pragma once

#include "vec.h"

class Rigidbody2D {
private:
  float mass = 1.f;
  float density = 1.f;
  Vec2 velocity = {0.f, 0.f};

public:
  float GetMass() { return mass; };
  void SetMass(float mass) { this->mass = mass; };

  float GetDensity() { return density; };
  void SetDensity(float density) { this->density = density; };

  Vec2 GetVeclocity() { return velocity; };
  void SetVeclocity(const Vec2 &velocity) { this->velocity = velocity; };
};
