#include "ass_03.h"
#include "core.h"
#include "pi.h"
#include "render.h"
#include "sys.h"
#include "vec.h"

void Ass03::Start() {
  // Ball initialization
  for (int i = 0; i < BALLS_NUM; i++) {
    auto pos = Vec2(CORE_FRand(0., SCR_WIDTH), CORE_FRand(0., SCR_HEIGHT));
    auto speedX = CORE_FRand(-maxBallSpeed, maxBallSpeed);
    auto speedY = CORE_FRand(-maxBallSpeed, maxBallSpeed);
    auto radius = CORE_FRand(minBallRadius, maxBallRadius);
    auto area = radius * PI * PI;
    auto density = 1.f;
    auto mass = area * density;

    balls[i].pos = pos;
    balls[i].vel = Vec2(speedX, speedY);
    balls[i].radius = radius;
    balls[i].mass = mass;
    balls[i].gfx = Render::GetTxBall();
  }
}

void Ass03::Update() {}

void Ass03::Fixed() {}

void Ass03::End() {}
