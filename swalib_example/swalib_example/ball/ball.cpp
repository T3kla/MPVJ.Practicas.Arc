#include "ball.h"

Ball::Ball() : pos(0.f), vel(0.f), gfx(0), radius(0.f), mass(0.f)
{
}

vec2 Ball::get_momentum()
{
    return vel * mass;
}
