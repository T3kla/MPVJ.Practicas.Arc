#pragma once

#include "component_manager.h"
#include "entity_manager.h"
#include "system_manager.h"
#include <memory>

class ECS {
private:                     // SINGLETONE STUFF
  ECS();                     //
  static ECS instance;       //
public:                      //
  ECS(const ECS &) = delete; //
  static ECS &Get();         //

private:
  std::unique_ptr<ComponentMan> cmpMan;
  std::unique_ptr<EntityMan> entMan;
  std::unique_ptr<SystemMan> sysMan;

public:
  void Init();

  EntID CreateEntity();
  void DestroyEntity(EntID id);

  template <typename T> void RegisterComponent();
  template <typename T> void AddComponent(EntID id, T component);
  template <typename T> void RemoveComponent(EntID id);
  template <typename T> T &GetComponent(EntID id);
  template <typename T> CmpID GetComponentID();

  template <typename T> std::shared_ptr<T> RegisterSystem();
  template <typename T> void SetSystemSignature(Signature signature);
};
