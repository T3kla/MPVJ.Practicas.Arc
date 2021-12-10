#pragma once

#include "ball.h"
#include "gameobject.h"

constexpr unsigned int BALLS_NUM = 30;

class Ass03 : public GameObject {
private:
  float maxBallSpeed = 100.f;
  float maxBallRadius = 20.f;
  float minBallRadius = 10.f;
  Ball balls[BALLS_NUM];

public:
  float GetMaxBallSpeed() const { return maxBallSpeed; }
  float GetMaxBallRadius() const { return maxBallRadius; }
  float GetMinBallRadius() const { return minBallRadius; }
  const Ball *GetBalls() const { return balls; }

  // Inherited via GameObject
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void End() override;
};
