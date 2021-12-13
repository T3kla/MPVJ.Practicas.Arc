#pragma once

struct CircleCollider {
  bool isTrigger = false;
  float radius = 0.f;

  CircleCollider(bool isTrigger = false, float radius = 1.f)
      : isTrigger(isTrigger), radius(radius){};
};
