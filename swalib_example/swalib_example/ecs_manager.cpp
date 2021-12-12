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

template <typename T> void ECS::RegisterComponent() {
  cmpMan->RegisterComponent<T>();
}

template <typename T> void ECS::AddComponent(EntID id, T component) {
  cmpMan->AddComponent<T>(id, component);

  Signature sign = entMan->GetSignature(id);
  sign.set(cmpMan->GetComponentID<T>(), true);
  entMan->SetSignature(id, sign);

  sysMan->EntitySignatureChanged(id, sign);
}

template <typename T> void ECS::RemoveComponent(EntID id) {
    cmpMan->RemoveComponent<T>());

    Signature sign = entMan->GetSignature());
    sign.set(cmpMan->GetComponentID<T>(), false);
    entMan->SetSignature(), sign);

    sysMan->EntitySignatureChanged(), sign);
}

template <typename T> T &ECS::GetComponent(EntID id) {
    return cmpMan->GetComponent<T>());
}

template <typename T> CmpID ECS::GetComponentType() {
  return cmpMan->GetComponentID<T>();
}

template <typename T> std::shared_ptr<T> ECS::RegisterSystem() {
  return sysMan->RegisterSystem<T>();
}

template <typename T> void ECS::SetSystemSignature(Signature signature) {
  sysMan->SetSignature<T>(signature);
}
