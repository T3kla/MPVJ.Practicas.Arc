#pragma once

#include "../common/stdafx.h"
#include "vector2d.h"

struct Ball // Info Ball
{
    vec2 pos;     // Position.
    vec2 vel;     // Velocity.
    GLuint gfx;   // OpenGL for id. for visualization purposes.
    float radius; // Radius.

    Ball();
};
