#pragma once

#include "ball.h"
#include "gameobject.h"
#include "sys_physics.h"
#include "sys_renderer.h"
#include <memory>

constexpr unsigned int BALLS_NUM = 30;

class Ass03 : public GameObject {
private:
  float maxBallSpeed = 100.f;
  float maxBallRadius = 20.f;
  float minBallRadius = 10.f;
  Ball balls[BALLS_NUM];

  std::shared_ptr<SysPhysics> physics = nullptr;
  std::shared_ptr<SysRenderer> renderer = nullptr;

public:
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void End() override;
};
