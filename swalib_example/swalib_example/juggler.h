#pragma once

#include "entity_manager.h"
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
  size_t GetSize() const { return size; }

  void AddComponent(EntID id, const T &cmp) {
    if (ent_idx.find(id) != ent_idx.end())
      throw "Retrieving non-existent component.";

    ent_idx[id] = size;
    idx_ent[size] = id;
    data[size] = cmp;
    ++size;
  }

  T &GetComponent(EntID id) {
    if (ent_idx.find(id) == ent_idx.end())
      throw "Retrieving non-existent component.";

    return data[ent_idx[id]];
  }

  void RemoveComponent(EntID id) {
    if (ent_idx.find(id) == ent_idx.end())
      throw "Retrieving non-existent component.";

    // Move data from botton to now-empty spot
    size_t oldEntityIndex = ent_idx[id];
    size_t lastEntityIndex = size - 1;
    data[oldEntityIndex] = data[lastEntityIndex];

    // Update maps
    EntID movedEntityID = idx_ent[lastEntityIndex];
    ent_idx[movedEntityID] = oldEntityIndex;
    idx_ent[oldEntityIndex] = movedEntityID;

    ent_idx.erase(id);
    idx_ent.erase(lastEntityIndex);

    --size;
  }

  virtual void EntityDestroyed(EntID id) override {
    if (ent_idx.find(id) != ent_idx.end())
      RemoveComponent(id);
  }
};
