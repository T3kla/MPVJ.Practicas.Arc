#pragma once

#include "component.h"
#include "component_registry.h"
#include <map>
#include <vector>

class Entity {
  std::map<int, Component *> components;

public:
  Entity();
  ~Entity();

  template <class T> T *GetComponent() const;
  template <class T> void AddComponent(T component);

  virtual void Slot();
};

template <class T> inline T *Entity::GetComponent() const {
  int cmpID = CmpRegistry::GetComponentID<T>();
  auto it = components.find(typeName);

  if (it != components.end())
    return true;

  return (T *)it->second;
}

template <class T> inline void Entity::AddComponent(T component) {
  int cmpID = CmpRegistry::GetComponentID<T>();

  auto it = components.find(typeName);
  if (it != components.end()) {
    delete it->second;
    it->second = new component;
    return;
  }

  components.insert({cmpID, new component});
}
