#include "ball.h"

Ball::Ball() : pos(0.f), vel(0.f), gfx(0), radius(0.f), mass(0.f) {}

Vec2 Ball::GetMomentum() { return vel * mass; }
