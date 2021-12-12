#pragma once

#include "entity_manager.h"
#include "juggler.h"
#include <memory>
#include <unordered_map>

// Register components to generate their juggler and id

class ComponentMan {
private:
  std::unordered_map<const char *, CmpID> name_id{};
  std::unordered_map<const char *, std::shared_ptr<IJuggler>> name_juggler{};
  CmpID cmpCount = 0;

  template <typename T> std::shared_ptr<Juggler<T>> GetJuggler();

public:
  template <typename T> CmpID GetComponentID() const;
  template <typename T> void RegisterComponent();

  template <typename T> void AddComponent(EntID id, const T &cmp) const;
  template <typename T> T &GetComponent(EntID id) const;
  template <typename T> void RemoveComponent(EntID id) const;

  void EntityDestroyed(EntID id) const;
};
