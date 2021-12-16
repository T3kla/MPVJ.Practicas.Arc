#pragma once

#include "ball.h"
#include "object.h"
#include <memory>

constexpr int BALLS_NUM = 50;
constexpr float MAX_SPEED = 100.f;
constexpr float MAX_RADIUS = 20.f;
constexpr float MIN_RADIUS = 10.f;

class Practica03 : public Object {
private:
  std::vector<Ball> balls;

public:
  Practica03();
  ~Practica03();

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;
};
