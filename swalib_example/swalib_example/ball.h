#pragma once

#include "stdafx.h"
#include "vector2d.h"

struct Ball // Info Ball
{
  vec2 pos;
  vec2 vel;
  GLuint gfx; // OpenGL for id. for visualization purposes.
  float radius;
  float mass;

  Ball();

  vec2 get_momentum();
};
