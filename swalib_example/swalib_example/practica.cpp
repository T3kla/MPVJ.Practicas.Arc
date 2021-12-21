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

#include "entity.h"

Practica Practica::instance;
Practica::Practica() {}

void Practica::Init() { EngineGame::Subscribe(&instance); }

std::vector<Ball> *Practica::GetBalls() { return &instance.balls; }
std::vector<Entity> *Practica::GetEntities() { return &instance.entities; }

void Practica::Awake() {
  CmpRegistry::RegisterComponent<Transform>();
  CmpRegistry::RegisterComponent<CircleCollider>();
  CmpRegistry::RegisterComponent<SpriteRenderer>();
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

void Practica::Quit() { EngineGame::UnSubscribe(this); }
