#pragma once

#include "entity_manager.h"
#include <cassert>
#include <unordered_map>

// Array wrapper that ensures the data is tightly packed

class IJuggler {
public:
  // Replace with event subscription to OnEntityDesctruction in EntityMan
  // Maybe polling?
  virtual ~IJuggler() = default;
  virtual void EntityDestroyed(EntID id) = 0;
};

template <class T> class Juggler : public IJuggler {
private:
  std::array<T, MAX_ENTS> data;
  std::unordered_map<EntID, size_t> ent_idx;
  std::unordered_map<size_t, EntID> idx_ent;
  size_t size;

public:
  size_t GetSize() const;

  void AddComponent(EntID id, const T &cmp);
  T &GetComponent(EntID id) const;
  void RemoveComponent(EntID id);

  virtual void EntityDestroyed(EntID id) override;
};
