#include "practica.h"

#include <random>
#include <time.h>

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
std::vector<Entity *> *Practica::GetEntities() { return &instance.entities; }

void Practica::Awake() {}

void Practica::Start() {
  // Ball initialization

  std::default_random_engine rand((unsigned int)time(NULL));
  std::uniform_real_distribution<float> randPosX(0., SCR_WIDTH);
  std::uniform_real_distribution<float> randPosY(0., SCR_HEIGHT);
  std::uniform_real_distribution<float> randSpd(-MAX_SPEED, MAX_SPEED);
  std::uniform_real_distribution<float> randRad(MIN_RADIUS, MAX_RADIUS);

  entities.reserve(BALLS_NUM);

  for (int i = 0; i < BALLS_NUM; i++) {

    auto newBall = new Entity;

    Transform tf;
    RigidBody rb;
    CircleCollider cc;
    SpriteRenderer sr;

    do {
      Vec2 position = {randPosX(rand), randPosY(rand)};
      Vec2 velocity = {randSpd(rand), randSpd(rand)};
      GLuint texture = EngineRender::GetTxBall();
      float radius = randRad(rand);
      float mass = radius * powf((float)PI, 2);

      tf.position = position;
      rb.velocity = velocity;
      rb.mass = mass;
      cc.radius = radius;
      sr.textureID = texture;

    } while (CircleCollider::AnyOverlap(tf, cc, entities));

    newBall->AddComponent<Transform>(tf);
    newBall->AddComponent<RigidBody>(rb);
    newBall->AddComponent<CircleCollider>(cc);
    newBall->AddComponent<SpriteRenderer>(sr);

    entities.emplace_back(newBall);
  }

  EngineRender::SetBallVector(&entities);
}

void Practica::Update() {
  for (auto &ball : entities)
    ball->Slot();
}

void Practica::Fixed() {}

void Practica::Quit() {
  for (size_t i = 0; i < entities.size(); i++)
    entities[i]->RemoveAllComponents();

  entities.clear();

  EngineGame::UnSubscribe(this);
}
