#include "component_manager.h"

template <class T> std::shared_ptr<Juggler<T>> ComponentMan::GetJuggler() {
  const char *typeName = typeid(T).name();

  assert(name_id.find(typeName) != name_id.end() &&
         "Component not registered before use.");

  return std::static_pointer_cast<Juggler<T>>(name_juggler[typeName]);
}

template <class T> CmpID ComponentMan::GetComponentID() const {
  const char *typeName = typeid(T).name();

  assert(name_id.find(typeName) != name_id.end() &&
         "Component not registered before use.");

  return name_id[typeName];
}

template <class T> void ComponentMan::RegisterComponent() {
  const char *typeName = typeid(T).name();

  assert(name_id.find(typeName) == name_id.end() &&
         "Registering component type more than once.");

  name_id.insert({typeName, cmpCount});
  name_juggler.insert({typeName, std::make_shared<Juggler<T>>()});

  ++cmpCount;
}

template <class T>
void ComponentMan::AddComponent(EntID id, const T &cmp) const {
  GetJuggler<T>()->AddComponent(entity, cmp);
}

template <class T> void ComponentMan::RemoveComponent(EntID id) const {
  GetJuggler<T>()->RemoveComponent(id);
}

template <class T> T &ComponentMan::GetComponent(EntID id) const {
  return GetJuggler<T>()->GetComponent(id);
}

void ComponentMan::EntityDestroyed(EntID id) const {
  for (auto const &pair : name_juggler) {
    auto &cmp = pair.second;
    cmp->EntityDestroyed(id);
  }
}
