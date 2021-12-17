#pragma once

#include <unordered_map>

class CmpRegistry {
private:                                     // SINGLETON
  CmpRegistry();                             //
  static CmpRegistry instance;               //
  CmpRegistry(const CmpRegistry &) = delete; //

private:
  int count = 0;
  std::unordered_map<const char *, int> cmp_to_id = {};

public:
  template <class T> static bool IsRegistered();
  template <class T> static void RegisterComponent();
  template <class T> static int GetComponentID();
};

template <class T> inline bool CmpRegistry::IsRegistered() {
  const char *typeName = typeid(T).name();
  auto it = instance.cmp_to_id.find(typeName);

  if (it != instance.cmp_to_id.end())
    return true;

  return false;
}

template <class T> inline void CmpRegistry::RegisterComponent() {
  const char *typeName = typeid(T).name();
  instance.cmp_to_id.insert({typeName, instance.count++});
}

template <class T> inline int CmpRegistry::GetComponentID() {
  const char *typeName = typeid(T).name();
  auto it = instance.cmp_to_id.find(typeName);

  if (it != instance.cmp_to_id.end())
    return -1;

  return it->second;
}
