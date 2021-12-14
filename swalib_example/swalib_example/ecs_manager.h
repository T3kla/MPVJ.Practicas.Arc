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

  template <class T> void RegisterComponent() {
    cmpMan->RegisterComponent<T>();
  }

  template <class T> void AddComponent(EntID id, T component) {
    cmpMan->AddComponent<T>(id, component);

    Signature sign = entMan->GetSignature(id);
    sign.set(cmpMan->GetComponentID<T>(), true);
    entMan->SetSignature(id, sign);

    sysMan->EntitySignatureChanged(id, sign);
  }

  template <class T> void RemoveComponent(EntID id) {
    cmpMan->RemoveComponent<T>();

    Signature sign = entMan->GetSignature();
    sign.set(cmpMan->GetComponentID<T>(), false);
    entMan->SetSignature(id, sign);

    sysMan->EntitySignatureChanged(id, sign);
  }

  template <class T> T &GetComponent(EntID id) {
    return cmpMan->GetComponent<T>(id);
  }

  template <class T> CmpID GetComponentID() {
    return cmpMan->GetComponentID<T>();
  }

  template <class T> std::shared_ptr<T> RegisterSystem() {
    return sysMan->RegisterSystem<T>();
  }

  template <class T> std::shared_ptr<T> GetSystem() {
    return sysMan->GetSystem<T>();
  }

  template <class T> void SetSystemSignature(Signature signature) {
    sysMan->SetSignature<T>(signature);
  }
};
