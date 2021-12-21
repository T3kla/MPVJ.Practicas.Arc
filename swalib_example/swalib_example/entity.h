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
  template <class T> void RemoveComponent();

  virtual void Slot();
};

template <class T> inline T *Entity::GetComponent() const {
  int cmpID = CmpRegistry::GetComponentID<T>();
  auto it = components.find(cmpID);

  if (it != components.end())
    return nullptr;

  return (T *)it->second;
}

template <class T> inline void Entity::AddComponent(T component) {
  int cmpID = CmpRegistry::GetComponentID<T>();
  auto it = components.find(cmpID);

  if (it != components.end())
    return;

  Component *newCmp = new T(component);
  newCmp->owner = this;
  components.insert({cmpID, newCmp});
}

template <class T> inline void Entity::RemoveComponent() {
  int cmpID = CmpRegistry::GetComponentID<T>();
  auto it = components.find(cmpID);

  if (it == components.end())
    return;

  delete it->second;
  components.erase(it);
}
