#pragma once

#include "component.h"
#include "msg.h"
#include <unordered_map>

class Entity {
private:
  std::unordered_map<const char *, void *> components;

  template <class T> const char *GetCmpID() const;

public:
  Entity();
  ~Entity();

  template <class T> T *GetComponent() const;
  template <class T> void AddComponent(const T &component);
  template <class T> void RemoveComponent();

  void SendMessageNoWin(Msg *msg);
  void RemoveAllComponents();

  virtual void Slot();
};

template <class T> inline const char *Entity::GetCmpID() const {
  return typeid(T).name();
};

template <class T> inline T *Entity::GetComponent() const {
  auto id = GetCmpID<T>();
  auto it = components.find(id);

  if (it == components.end())
    return nullptr;

  return (T *)it->second;
}

template <class T> inline void Entity::AddComponent(const T &component) {
  auto id = GetCmpID<T>();
  auto it = components.find(id);

  if (it != components.end())
    return;

  Component *newCmp = new T(component);
  newCmp->owner = this;
  components.insert({id, newCmp});
}

template <class T> inline void Entity::RemoveComponent() {
  auto id = GetCmpID<T>();
  auto it = components.find(id);

  if (it == components.end())
    return;

  delete it->second;
  components.erase(it);
}
