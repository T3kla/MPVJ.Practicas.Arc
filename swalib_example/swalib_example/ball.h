#pragma once

#include "stdafx.h"
#include "vec.h"
#include "vector2d.h"

struct Ball // Info Ball
{
  Vec2 pos;
  Vec2 vel;
  GLuint gfx;
  float radius;
  float mass;

  Ball();

  Vec2 GetMomentum();
};
