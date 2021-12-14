#pragma once

#include "entity.h"
#include "gameobject.h"
#include "sys_physics.h"
#include "sys_renderer.h"
#include <memory>

constexpr int BALLS_NUM = 150;

class Ass03 : public GameObject {
private:
  float maxBallSpeed = 1000.f;
  float maxBallRadius = 40.f;
  float minBallRadius = 20.f;

  std::vector<Entity> balls;
  std::shared_ptr<SysPhysics> physics = nullptr;
  std::shared_ptr<SysRenderer> renderer = nullptr;

public:
  Ass03();
  ~Ass03();

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void End() override;
};
