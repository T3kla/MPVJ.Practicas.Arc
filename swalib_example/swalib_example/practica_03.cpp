#include "practica_03.h"

#include "core.h"
#include "engine_game.h"
#include "engine_render.h"
#include "pi.h"
#include "stasis.h"
#include "stdafx.h"
#include "sys.h"
#include "vec.h"
#include <random>

Practica03::Practica03() { EngineGame::Subscribe(this); }
Practica03::~Practica03() { EngineGame::UnSubscribe(this); }

void Practica03::Awake() {}

void Practica03::Start() {
  // Ball initialization
  std::default_random_engine rand(Stasis::GetDelta());
  std::uniform_real_distribution<float> randPosX(0., SCR_WIDTH);
  std::uniform_real_distribution<float> randPosY(0., SCR_HEIGHT);
  std::uniform_real_distribution<float> randSpd(-MAX_SPEED, MAX_SPEED);
  std::uniform_real_distribution<float> randRad(MIN_RADIUS, MAX_RADIUS);

  for (int i = 0; i < BALLS_NUM; i++) {
    Vec2 position = {randPosX(rand), randPosY(rand)};
    Vec2 velocity = {randSpd(rand), randSpd(rand)};
    GLuint texture = EngineRender::GetTxBall();
    float radius = randRad(rand);
    float mass = radius * PI * PI;

    Ball newBall = {position, velocity, texture, radius, mass};
    balls.emplace_back(newBall);
  }

  EngineRender::SetBallVector(&balls);
}

void Practica03::Update() {
  for (auto &ball : balls)
    ball.Slot(&balls);
}
void Practica03::Fixed() {}

void Practica03::Quit() {}
