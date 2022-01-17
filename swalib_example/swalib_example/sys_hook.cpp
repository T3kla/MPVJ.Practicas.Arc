#include "sys_hook.h"

#include "sys.h"

#include "engine.h"
#include "engine_game.h"
#include "inputs.h"
#include "scene_01.h"
#include "sprite_loader.h"

#include "entity.h"

#include "ball.h"
#include "circle_collider.h"
#include "gameobject.h"
#include "hook.h"
#include "player.h"
#include "rigidbody.h"
#include "sprite_animation.h"
#include "sprite_renderer.h"
#include "sys_balls.h"
#include "transform.h"

Entity *GetHook();
bool IsCollidingCircLine(Vec2 circlePos, float circleRad, Vec2 point);

SysHook::SysHook() { EngineGame::Subscribe(this); }

SysHook::~SysHook() { EngineGame::UnSubscribe(this); }

void SysHook::Awake() {}

void SysHook::Start() {}

void SysHook::Update() {}

void SysHook::Fixed() {
  auto &reg = Scene_01::GetRegistry();

  // Travel
  for (auto &hook : reg) {
    auto *tf = hook->GetComponent<Transform>();
    auto *go = hook->GetComponent<GameObject>();
    auto *hk = hook->GetComponent<Hook>();

    if (!tf || !hk || !go->isActive)
      continue;

    tf->position += Vec2::Up() * hk->speed * (float)STP * 0.001f;
    if (tf->position.y > SCR_HEIGHT - 50)
      go->isActive = false;

    // Collisions
    for (auto &ball : reg) {
      auto *btf = ball->GetComponent<Transform>();
      auto *bgo = ball->GetComponent<GameObject>();
      auto *brb = ball->GetComponent<RigidBody>();
      auto *bbl = ball->GetComponent<Ball>();
      auto *bcl = ball->GetComponent<CircleCollider>();

      if (!btf || !bgo || !brb || !bbl || !bcl || !bgo->isActive)
        continue;

      if (IsCollidingCircLine(btf->position, bcl->radius, tf->position)) {
        go->isActive = false;
        bgo->isActive = false;
        auto size = bbl->size;
        SysBalls::InstantiateSmaller(btf->position, true, size);
        SysBalls::InstantiateSmaller(btf->position, false, size);
        return;
      }
    }
  }
}

void SysHook::Quit() {}

void SysHook::InstantiateHook(const Vec2 &pos) {
  auto *hook = GetHook();

  if (!hook)
    return;

  auto *tf = hook->GetComponent<Transform>();
  auto *go = hook->GetComponent<GameObject>();
  auto *hk = hook->GetComponent<Hook>();
  auto *sr = hook->GetComponent<SpriteRenderer>();
  auto *sa = hook->GetComponent<SpriteAnimation>();

  tf->position = pos;

  go->isActive = true;

  hk->speed = -1000.f;

  sr->sprite = &SpriteLoader::sprHook[0];
  sr->offsetPosition = {0.f, -420.f};
  sr->offsetRotation = 0.f;
  sr->size = {100.f, 1000.f};
  sr->pivot = {0.5f, 0.5f};
  sr->layer = 5;

  sa->animation = &SpriteLoader::sprHook;
  sa->duration = 0.2f;
  sa->count = 0.f;
  sa->frame = 0;
  sa->enable = true;
}

Entity *GetHook() {
  auto &reg = Scene_01::GetRegistry();

  // Pooling
  for (auto &i : reg) {
    auto *gaob = i->GetComponent<GameObject>();
    auto *hook = i->GetComponent<Hook>();

    if (gaob && hook && !gaob->isActive)
      return i;
  }

  // Instantiation
  auto hook = new Entity();

  auto tf = Transform();
  auto go = GameObject();
  auto hk = Hook();
  auto sr = SpriteRenderer();
  auto sa = SpriteAnimation();

  hook->AddComponent<Transform>(&tf);
  hook->AddComponent<GameObject>(&go);
  hook->AddComponent<Hook>(&hk);
  hook->AddComponent<SpriteRenderer>(&sr);
  hook->AddComponent<SpriteAnimation>(&sa);

  reg.push_back(hook);
  return hook;
}

bool IsCollidingCircLine(Vec2 circlePos, float circleRad, Vec2 point) {
  for (size_t i = 0; i < 500; i++) {
    auto p = point - Vec2(-15.f, -10.f + 5.f * i);
    auto toSphere = circlePos - p;

    if (toSphere.Magnitude() < circleRad - 10.f)
      return true;
  }
  return false;
}
