#pragma once

#include <vector>

#include "sprite.h"

struct SpriteAnimation {
  std::vector<Sprite> *animation = nullptr;

  // bool enabled = true;

  // int frame2 = 0;
  // int frame = 0;
  // float speed = 0.f;

  float duration = 0.f;
  float count = 0.f;

  // float count1 = 0.f;
  // float count2 = 0.f;
  // float count3 = 0.f;
  // float count4 = 0.f;
};
