#include "practica.h"

#include "core.h"
#include "engine_game.h"
#include "engine_render.h"
#include "pi.h"
#include "stasis.h"
#include "stdafx.h"
#include "sys.h"
#include "vec.h"
#include <random>

Practica::Practica() { EngineGame::Subscribe(this); }
Practica::~Practica() { EngineGame::UnSubscribe(this); }

void Practica::Awake() {}

void Practica::Start() {
  // Ball initialization
  std::default_random_engine rand((unsigned int)Stasis::GetDelta());
  std::uniform_real_distribution<float> randPosX(0., SCR_WIDTH);
  std::uniform_real_distribution<float> randPosY(0., SCR_HEIGHT);
  std::uniform_real_distribution<float> randSpd(-MAX_SPEED, MAX_SPEED);
  std::uniform_real_distribution<float> randRad(MIN_RADIUS, MAX_RADIUS);

  for (int i = 0; i < BALLS_NUM; i++) {
    Ball newBall = {};
    do {
      Vec2 position = {randPosX(rand), randPosY(rand)};
      Vec2 velocity = {randSpd(rand), randSpd(rand)};
      GLuint texture = EngineRender::GetTxBall();
      float radius = randRad(rand);
      float mass = radius * powf((float)PI, 2);

      newBall = {position, velocity, texture, radius, mass};
    } while (newBall.IsColliding(&balls)); // No overlap at awake

    balls.emplace_back(newBall);
  }

  EngineRender::SetBallVector(&balls);
}

void Practica::Update() {
  for (auto &ball : balls)
    ball.Slot(&balls);
}
void Practica::Fixed() {}

void Practica::Quit() {}
