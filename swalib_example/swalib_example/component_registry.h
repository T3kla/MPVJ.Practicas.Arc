#pragma once

#include <unordered_map>
#include <unordered_set>

class CmpRegistry {
private:                                     // SINGLETON
  CmpRegistry();                             //
  static CmpRegistry instance;               //
  CmpRegistry(const CmpRegistry &) = delete; //

private:
  int count = 0;
  std::unordered_map<const char *, int> cmp_to_id = {};
  std::unordered_set<const char *> set = {};

public:
  template <class T> static int GetComponentID();
};

template <class T> inline int CmpRegistry::GetComponentID() {
  const char *typeName = typeid(T).name();

  instance.set.insert(typeName);

  for (auto &id : instance.cmp_to_id)
    if (strcmp(typeName, id.first) == 0)
      return id.second;

  instance.cmp_to_id.insert({typeName, instance.count++});
  return instance.count - 1;
}
