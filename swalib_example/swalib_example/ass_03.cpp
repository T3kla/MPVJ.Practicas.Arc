#include "ass_03.h"

#include <random>

#include "core.h"
#include "sys.h"

#include "engine_game.h"
#include "engine_render.h"
#include "entity.h"

#include "pi.h"
#include "vec.h"

#include "ecs_manager.h"
//#include "entity_manager.h"
//#include "component_manager.h"
//#include "system_manager.h"

#include "circle_collider.h"
#include "rigidbody_2d.h"
#include "sprite_renderer.h"
#include "transform_2d.h"

Ass03::Ass03() { EngineGame::Subscribe(this); }
Ass03::~Ass03() { EngineGame::UnSubscribe(this); }

void Ass03::Start() {
  // ECS initialization
  auto &ecs = ECS::Get();
  ecs.Init();

  //    Component Registration
  ecs.RegisterComponent<Transform2D>();
  ecs.RegisterComponent<Rigidbody2D>();
  ecs.RegisterComponent<CircleCollider>();
  ecs.RegisterComponent<SpriteRenderer>();

  //    System Registration
  physics = ecs.RegisterSystem<SysPhysics>();
  renderer = ecs.RegisterSystem<SysRenderer>();

  //    Physics system
  Signature signPhysics;
  signPhysics.set(ecs.GetComponentID<Transform2D>());
  signPhysics.set(ecs.GetComponentID<Rigidbody2D>());
  signPhysics.set(ecs.GetComponentID<CircleCollider>());
  ecs.SetSystemSignature<SysPhysics>(signPhysics);

  //    Render system
  Signature signRenderer;
  signRenderer.set(ecs.GetComponentID<SpriteRenderer>());
  ecs.SetSystemSignature<SysRenderer>(signRenderer);

  std::default_random_engine rand;
  std::uniform_real_distribution<float> randPosX(0., SCR_WIDTH);
  std::uniform_real_distribution<float> randPosY(0., SCR_HEIGHT);
  std::uniform_real_distribution<float> randSpd(-maxBallSpeed, maxBallSpeed);
  std::uniform_real_distribution<float> randRad(minBallRadius, maxBallRadius);

  // Ball initialization
  balls = std::vector<Ball>(BALLS_NUM);
  for (int i = 0; i < BALLS_NUM; i++) {
    auto id = ecs.CreateEntity();

    auto radius = randRad(rand);
    auto area = radius * PI * PI;

    balls[i].SetEntID(id);

    Transform2D tf;
    tf.position = {randPosX(rand), randPosY(rand)};
    tf.rotation = 0.f;
    tf.scale = {radius, radius};
    ecs.AddComponent(id, tf);

    Rigidbody2D rb;
    rb.mass = 1.f;
    rb.velocity = {randSpd(rand), randSpd(rand)};
    ecs.AddComponent(id, rb);

    CircleCollider cc;
    cc.isTrigger = false;
    cc.radius = radius;
    ecs.AddComponent(id, cc);

    SpriteRenderer sr;
    sr.scale = {1.f, 1.f};
    sr.texture = EngineRender::GetTxBall();
    ecs.AddComponent(id, sr);
  }
}

void Ass03::Update() {
  for (auto &ball : balls)
    ball.EarlyUpdate();

  physics->Run();
  renderer->Run();

  for (auto &ball : balls)
    ball.Update();
  for (auto &ball : balls)
    ball.LateUpdate();
}

void Ass03::Fixed() {}

void Ass03::End() {}
