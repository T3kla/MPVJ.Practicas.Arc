#pragma once

#include "ball.h"
#include "entity.h"
#include "object.h"
#include <memory>
#include <vector>

constexpr int BALLS_NUM = 10;
constexpr float MAX_SPEED = 100.f;
constexpr float MAX_RADIUS = 20.f;
constexpr float MIN_RADIUS = 10.f;

class Practica : public Object {
private:                               // SINGLETON
  Practica();                          //
  static Practica instance;            //
public:                                //
  Practica(const Practica &) = delete; //

public:
  std::vector<Ball> balls;
  std::vector<Entity> entities;

  static void Init();
  static std::vector<Ball> *GetBalls();
  static std::vector<Entity> *GetEntities();

private:
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;
};
