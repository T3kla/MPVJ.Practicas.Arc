#pragma once

#include "vec.h"

class Transform2D {
private:
  Vec2 position = {0.f, 0.f};
  float rotation = 0.f;
  Vec2 scale = {0.f, 0.f};

public:
  Vec2 GetPosition() { return position; };
  void SetPosition(const Vec2 &position) { this->position = position; };

  float GetRotation() { return rotation; };
  void SetRotation(float rotation) { this->rotation = rotation; };

  Vec2 GetScale() { return scale; };
  void SetScale(const Vec2 &scale) { this->scale = scale; };
};
