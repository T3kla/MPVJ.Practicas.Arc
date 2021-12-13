#pragma once

#include "entity.h"

struct Ball : public Entity {
  Ball(){};
  ~Ball(){};

  virtual void EarlyUpdate() override;
  virtual void Update() override;
  virtual void LateUpdate() override;
};
