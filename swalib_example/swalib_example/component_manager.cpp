#include "component_manager.h"

template <typename T>
inline std::shared_ptr<Juggler<T>> ComponentMan::GetJuggler() {
  const char *typeName = typeid(T).name();

  assert(name_id.find(typeName) != name_id.end() &&
         "Component not registered before use.");

  return std::static_pointer_cast<Juggler<T>>(name_juggler[typeName]);
}

template <typename T> inline CmpID ComponentMan::GetComponentID() const {
  const char *typeName = typeid(T).name();

  assert(name_id.find(typeName) != name_id.end() &&
         "Component not registered before use.");

  return name_id[typeName];
}

template <typename T> inline void ComponentMan::RegisterComponent() {
  const char *typeName = typeid(T).name();

  assert(name_id.find(typeName) == name_id.end() &&
         "Registering component type more than once.");

  name_id.insert({typeName, cmpCount});
  name_juggler.insert({typeName, std::make_shared<Juggler<T>>()});

  ++cmpCount;
}

template <typename T>
inline void ComponentMan::AddComponent(EntID id, const T &cmp) const {
  GetJuggler<T>()->AddComponent(entity, cmp);
}

template <typename T>
inline void ComponentMan::RemoveComponent(EntID id) const {
  GetJuggler<T>()->RemoveComponent(entity);
}

template <typename T> inline T &ComponentMan::GetComponent(EntID id) const {
  return GetJuggler<T>()->GetComponent(entity);
}

inline void ComponentMan::EntityDestroyed(EntID id) const {
  for (auto const &pair : name_juggler) {
    auto &cmp = pair.second;
    cmp->EntityDestroyed(id);
  }
}
