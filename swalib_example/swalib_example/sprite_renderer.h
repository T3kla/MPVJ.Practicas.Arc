#pragma once

#include "stdafx.h"
#include "vec.h"

struct SpriteRenderer {
  Vec2 scale = {1.f, 1.f};
  GLuint texture = 0;
};
