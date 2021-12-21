#pragma once

#include "component.h"
#include "stdafx.h"

struct SpriteRenderer : public Component {
  GLuint textureID = 0;
  virtual void Slot() override{};
};
