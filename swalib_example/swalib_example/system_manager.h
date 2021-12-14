#pragma once

#include "entity_manager.h"
#include "system.h"
#include <memory>
#include <unordered_map>

class SystemMan {
private:
  std::unordered_map<const char *, Signature> name_sign{};
  std::unordered_map<const char *, std::shared_ptr<System>> name_sys{};

public:
  template <class T> std::shared_ptr<T> RegisterSystem() {
    const char *typeName = typeid(T).name();

    if (name_sys.find(typeName) != name_sys.end())
      throw "Registering system more than once.";

    auto system = std::make_shared<T>();
    name_sys.insert({typeName, system});
    return system;
  }

  template <class T> std::shared_ptr<T> GetSystem() {
    const char *typeName = typeid(T).name();
    auto it = name_sys.find(typeName);

    if (it == name_sys.end())
      throw "Can't find requested system.";

    return std::static_pointer_cast<T>(it->second);
  }

  template <class T> void SetSignature(Signature sign) {
    const char *typeName = typeid(T).name();

    if (name_sys.find(typeName) == name_sys.end())
      throw "System used before registered.";

    name_sign.insert({typeName, sign});
  }

  void EntityDestroyed(EntID id) {
    for (auto const &pair : name_sys)
      pair.second->entities.erase(id);
  }

  void EntitySignatureChanged(EntID id, const Signature &sign) {
    // Ensures each system has a list of entities that
    // share the system's signature
    for (auto const &pair : name_sys) {
      auto const &type = pair.first;
      auto const &system = pair.second;
      auto const &systemSignature = name_sign[type];

      // If entity has this system's signature
      if ((sign & systemSignature) == systemSignature)
        system->entities.insert(id);
      else
        system->entities.erase(id);
    }
  }
};
