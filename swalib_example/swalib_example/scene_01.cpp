#include "scene_01.h"

#include "engine_game.h"
#include "sys_balls.h"
#include "sys_hook.h"
#include "sys_physics.h"
#include "sys_player.h"

#include "vec.h"

#include "entity.h"

std::vector<Entity *> Scene_01::reg;

Scene_01 Scene_01::instance;
Scene_01::Scene_01() {}

void Scene_01::Load() { EngineGame::Subscribe(&instance); }

std::vector<Entity *> &Scene_01::GetRegistry() { return reg; }

void Scene_01::Awake() {}

void Scene_01::Start() {

  SysBalls::InstantiateBallL({300.f, 500.f}, true);
  SysBalls::InstantiateBallB({600.f, 500.f}, true);
  SysBalls::InstantiateBallM({800.f, 500.f}, true);
  SysBalls::InstantiateBallS({1000.f, 500.f}, true);

  // Systems
  new SysPlayer();
  new SysPhysics();
  new SysHook();
  new SysBalls();
}

void Scene_01::Update() {}

void Scene_01::Fixed() {}

void Scene_01::Quit() {
  for (auto &entity : reg)
    entity->RemoveAllComponents();

  reg.clear();

  EngineGame::UnSubscribe(this);
}
