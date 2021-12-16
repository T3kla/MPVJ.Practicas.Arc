#include "ass_03.h"

#include "circle_collider.h"
#include "core.h"
#include "ecs_manager.h"
#include "engine_game.h"
#include "engine_render.h"
#include "entity.h"
#include "pi.h"
#include "rigidbody_2d.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys.h"
#include "transform_2d.h"
#include "vec.h"
#include <random>

Ass03::Ass03() { EngineGame::Subscribe(this); }
Ass03::~Ass03() { EngineGame::UnSubscribe(this); }

void Ass03::Awake() {
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
}

void Ass03::Start() {
  auto &ecs = ECS::Get();

  // Ball initialization
  std::default_random_engine rand(Stasis::GetDelta());
  std::uniform_real_distribution<float> randPosX(0., SCR_WIDTH);
  std::uniform_real_distribution<float> randPosY(0., SCR_HEIGHT);
  std::uniform_real_distribution<float> randSpd(-maxBallSpeed, maxBallSpeed);
  std::uniform_real_distribution<float> randRad(minBallRadius, maxBallRadius);

  balls = std::vector<Entity>(BALLS_NUM);
  for (int i = 0; i < BALLS_NUM; i++) {
    auto id = ecs.CreateEntity();

    auto radius = randRad(rand);
    auto area = radius * PI * PI;

    balls[i].SetEntID(id);

    Transform2D tf; // TODO: prevent initial overlapping
    tf.position = {randPosX(rand), randPosY(rand)};
    tf.rotation = 0.f;
    tf.scale = {radius / 2.f, radius / 2.f};
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
    sr.scale = {radius, radius};
    sr.texture = EngineRender::GetTxBall();
    ecs.AddComponent(id, sr);
  }
}

void Ass03::Update() {
  physics->Run();
  // renderer->Run();
}

void Ass03::Fixed() {}

void Ass03::End() {}
