#include "practica.h"

#include <random>

#include "core.h"
#include "stdafx.h"
#include "sys.h"

#include "engine_game.h"
#include "engine_render.h"
#include "stasis.h"

#include "pi.h"
#include "vec.h"

#include "circle_collider.h"
#include "component_registry.h"
#include "sprite_renderer.h"
#include "transform.h"

Practica::Practica() { EngineGame::Subscribe(this); }
Practica::~Practica() { EngineGame::UnSubscribe(this); }

void Practica::Awake() {
  CmpRegistry::RegisterComponent<Transform>(); // TODO: a ver si registra
  auto a = CmpRegistry::GetComponentID<Transform>();
  CmpRegistry::RegisterComponent<CircleCollider>();
  auto b = CmpRegistry::GetComponentID<CircleCollider>();
  CmpRegistry::RegisterComponent<SpriteRenderer>();
  auto c = CmpRegistry::GetComponentID<SpriteRenderer>();
}

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
