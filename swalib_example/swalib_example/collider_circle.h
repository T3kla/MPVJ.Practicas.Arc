#pragma once

class ColliderCircle {
private:
  bool is_trigger = false;
  float radius = 0.f;

public:
  bool GetIsTrigger() { return is_trigger; };
  void SetIsTrigger(bool is_trigger) { this->is_trigger = is_trigger; };

  float GetRadius() { return radius; };
  void SetRadius(float radius) { this->radius = radius; };
};
