#pragma once

#include "ball.h"
#include "gameobject.h"
#include <memory>

constexpr int BALLS_NUM = 50;
constexpr float MAX_SPEED = 100.f;
constexpr float MAX_RADIUS = 20.f;
constexpr float MIN_RADIUS = 10.f;

class Ass03 : public GameObject {
private:
  std::vector<Ball> balls;

public:
  Ass03();
  ~Ass03();

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;
};
