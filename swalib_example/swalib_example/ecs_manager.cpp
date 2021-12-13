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

template <class T> void ECS::RegisterComponent() {
  cmpMan->RegisterComponent<T>();
}

template <class T> void ECS::AddComponent(EntID id, T component) {
  cmpMan->AddComponent<T>(id, component);

  Signature sign = entMan->GetSignature(id);
  sign.set(cmpMan->GetComponentID<T>(), true);
  entMan->SetSignature(id, sign);

  sysMan->EntitySignatureChanged(id, sign);
}

template <class T> void ECS::RemoveComponent(EntID id) {
  cmpMan->RemoveComponent<T>();

  Signature sign = entMan->GetSignature();
  sign.set(cmpMan->GetComponentID<T>(), false);
  entMan->SetSignature(id, sign);

  sysMan->EntitySignatureChanged(id, sign);
}

template <class T> T &ECS::GetComponent(EntID id) {
  return cmpMan->GetComponent<T>(id);
}

template <class T> CmpID ECS::GetComponentID() {
  return cmpMan->GetComponentID<T>();
}

template <class T> std::shared_ptr<T> ECS::RegisterSystem() {
  return sysMan->RegisterSystem<T>();
}

template <class T> void ECS::SetSystemSignature(Signature signature) {
  sysMan->SetSignature<T>(signature);
}
