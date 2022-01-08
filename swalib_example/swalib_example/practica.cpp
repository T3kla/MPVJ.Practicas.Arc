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
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "transform.h"

#include "entity.h"

Practica Practica::instance;
Practica::Practica() {}

void Practica::Init() { EngineGame::Subscribe(&instance); }

std::vector<Ball> *Practica::GetBalls() { return &instance.balls; }
std::vector<Entity> *Practica::GetEntities() { return &instance.entities; }

void Practica::Awake() {}

void Practica::Start() {
  // Ball initialization
  std::default_random_engine rand((unsigned int)Stasis::GetDelta());
  std::uniform_real_distribution<float> randPosX(0., SCR_WIDTH);
  std::uniform_real_distribution<float> randPosY(0., SCR_HEIGHT);
  std::uniform_real_distribution<float> randSpd(-MAX_SPEED, MAX_SPEED);
  std::uniform_real_distribution<float> randRad(MIN_RADIUS, MAX_RADIUS);

  for (int i = 0; i < BALLS_NUM; i++) {
    Entity newBall = {};
    do {
      Vec2 position = {randPosX(rand), randPosY(rand)};
      Vec2 velocity = {randSpd(rand), randSpd(rand)};
      GLuint texture = EngineRender::GetTxBall();
      float radius = randRad(rand);
      float mass = radius * powf((float)PI, 2);

      Transform tf = {};
      tf.position = position;
      newBall.AddComponent<Transform>(tf);

      RigidBody rb = {};
      rb.velocity = velocity;
      rb.mass = mass;
      newBall.AddComponent<RigidBody>(rb);

      CircleCollider cc = {};
      cc.radius = radius;
      newBall.AddComponent<CircleCollider>(cc);

      SpriteRenderer sr = {};
      sr.textureID = texture;
      newBall.AddComponent<SpriteRenderer>(sr);

    } while (newBall.GetComponent<CircleCollider>()->IsColliding(
        &entities)); // No overlap at awake

    entities.emplace_back(newBall);
  }
}

void Practica::Update() {
  for (auto &ball : entities) {
    ball.GetComponent<Transform>()->Slot();
    ball.GetComponent<RigidBody>()->Slot();
    ball.GetComponent<CircleCollider>()->Slot();
    ball.GetComponent<SpriteRenderer>()->Slot();
  }
}

void Practica::Fixed() {}

void Practica::Quit() { EngineGame::UnSubscribe(this); }
