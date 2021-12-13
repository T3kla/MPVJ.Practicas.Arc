#include "ecs_manager.h"

ECS ECS::instance;

ECS::ECS() {}

ECS &ECS::Get() { return instance; }

void ECS::Init() {
  cmpMan = std::make_unique<ComponentMan>();
  entMan = std::make_unique<EntityMan>();
  sysMan = std::make_unique<SystemMan>();
}

EntID ECS::CreateEntity() { return entMan->BorrowID(); }

void ECS::DestroyEntity(EntID id) {
  entMan->ReturnID(id);
  cmpMan->EntityDestroyed(id);
  sysMan->EntityDestroyed(id);
}
