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
  template <typename T> std::shared_ptr<T> RegisterSystem() {
    const char *typeName = typeid(T).name();

    assert(name_sys.find(typeName) == name_sys.end() &&
           "Registering system more than once.");

    auto system = std::make_shared<T>();
    name_sys.insert({typeName, system});
    return system;
  }

  template <typename T> void SetSignature(Signature signature) {
    const char *typeName = typeid(T).name();

    assert(name_sys.find(typeName) != name_sys.end() &&
           "System used before registered.");

    name_sign.insert({typeName, signature});
  }

  void EntityDestroyed(EntID id) {
    for (auto const &pair : name_sys)
      pair.second->entities.erase(id);
  }

  void EntitySignatureChanged(EntID id, const Signature &sign) {
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
