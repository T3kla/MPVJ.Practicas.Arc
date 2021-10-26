#pragma once

#include "..\math\vector2d.h"
#include "..\sys\stdafx.h"

struct Ball // Info Ball
{
    vec2 pos;     // Position.
    vec2 vel;     // Velocity.
    GLuint gfx;   // OpenGL for id. for visualization purposes.
    float radius; // Radius.

    Ball() : pos(0.0f), vel(0.0f), gfx(0), radius(0.0f)
    {
    }
};
