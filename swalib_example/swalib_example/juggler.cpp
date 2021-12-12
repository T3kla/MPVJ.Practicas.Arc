#include "juggler.h"

template <class T> inline size_t Juggler<T>::GetSize() const { return size; }

template <class T>
inline void Juggler<T>::AddComponent(EntID id, const T &cmp) {
  assert(ent_idx.find(id) == ent_idx.end() &&
         "Component added to same entity more than once.");

  ent_idx[id] = size;
  idx_ent[size] = id;
  data[size] = cmp;
  ++size;
}

template <class T> inline T &Juggler<T>::GetComponent(EntID id) const {
  assert(ent_idx.find(id) != ent_idx.end() &&
         "Retrieving non-existent component.");

  return data[ent_idx[id]];
}

template <class T> inline void Juggler<T>::RemoveComponent(EntID id) {
  assert(ent_idx.find(id) != ent_idx.end() &&
         "Removing non-existent component.");

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

template <class T> inline void Juggler<T>::EntityDestroyed(EntID id) {
  if (ent_idx.find(id) != ent_idx.end())
    RemoveComponent(id);
}
