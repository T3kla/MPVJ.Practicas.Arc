#include "ass_03.h"
#include "core.h"
#include "ecs_manager.h"
#include "engine_render.h"
#include "entity.h"
#include "sys.h"
#include <random>

#include "pi.h"
#include "vec.h"

#include "circle_collider.h"
#include "rigidbody_2d.h"
#include "sprite_renderer.h"
#include "transform_2d.h"

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
  for (int i = 0; i < BALLS_NUM; i++) {
    auto id = ecs.CreateEntity();

    auto radius = randRad(rand);
    auto area = radius * PI * PI;

    balls[i].SetEntID(id);
    ecs.AddComponent(id, Transform2D({{randPosX(rand), randPosY(rand)}}));
    ecs.AddComponent(id,
                     Rigidbody2D((float)area, {randSpd(rand), randSpd(rand)}));
    ecs.AddComponent(id, CircleCollider(false, radius));
    ecs.AddComponent(
        id, SpriteRenderer({radius, radius}, EngineRender::GetTxBall()));
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
