#pragma once

#include "entity.h"
#include "object.h"
#include <memory>
#include <vector>

constexpr int BALLS_NUM = 250;
constexpr float MAX_SPEED = 100.f;
constexpr float MAX_RADIUS = 20.f;
constexpr float MIN_RADIUS = 10.f;

class Practica : public Object {
private:                               // SINGLETON
  Practica();                          //
  ~Practica();                         //
  static Practica instance;            //
public:                                //
  Practica(const Practica &) = delete; //

private:
  std::vector<Entity> entities;

public:
  static std::vector<Entity> *GetEntities();

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;
};
