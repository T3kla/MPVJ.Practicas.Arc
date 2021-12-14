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

  template <class T> std::shared_ptr<Juggler<T>> GetJuggler() {
    const char *typeName = typeid(T).name();

    assert(name_id.find(typeName) != name_id.end() &&
           "Component not registered before use.");

    return std::static_pointer_cast<Juggler<T>>(name_juggler[typeName]);
  }

public:
  template <class T> CmpID GetComponentID() const {
    const char *typeName = typeid(T).name();
    auto it = name_id.find(typeName);

    assert(it != name_id.end() && "Component not registered before use.");

    return it->second;
  }

  template <class T> void RegisterComponent() {
    const char *typeName = typeid(T).name();

    assert(name_id.find(typeName) == name_id.end() &&
           "Registering component type more than once.");

    name_id.insert({typeName, cmpCount});
    name_juggler.insert({typeName, std::make_shared<Juggler<T>>()});

    ++cmpCount;
  }

  template <class T> void AddComponent(EntID id, const T &cmp) {
    GetJuggler<T>()->AddComponent(id, cmp);
  }

  template <class T> T &GetComponent(EntID id) {
    return GetJuggler<T>()->GetComponent(id);
  }

  template <class T> void RemoveComponent(EntID id) {
    GetJuggler<T>()->RemoveComponent(id);
  }

  void EntityDestroyed(EntID id) const;
};
