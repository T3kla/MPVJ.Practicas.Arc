#pragma once

#include "behaviour.h"

struct Vec2;

class SysBalls : public Behaviour {
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

public:
  SysBalls();
  ~SysBalls();

  static void SysBalls::InstantiateSmaller(const Vec2 &pos, bool right,
                                           char size);
  static void SysBalls::InstantiateBallL(const Vec2 &pos, bool right);
  static void SysBalls::InstantiateBallB(const Vec2 &pos, bool right);
  static void SysBalls::InstantiateBallM(const Vec2 &pos, bool right);
  static void SysBalls::InstantiateBallS(const Vec2 &pos, bool right);
};
