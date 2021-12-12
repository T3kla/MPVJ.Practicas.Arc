#include "entity_manager.h"
#include <cassert>

inline EntityMan::EntityMan() {
  for (EntID i = 0; i < MAX_ENTS; ++i)
    unusedIDs.push(i);
}

inline EntID EntityMan::BorrowID() {
  assert(count < MAX_ENTS && "Too many entities in existence.");

  EntID id = unusedIDs.front();
  unusedIDs.pop();
  ++count;

  return id;
}

inline void EntityMan::ReturnID(EntID id) {
  assert(id < MAX_ENTS && "Entity out of range.");

  name_sign[id].reset();

  unusedIDs.push(id);
  --count;
}

inline const Signature &EntityMan::GetSignature(EntID id) const {
  assert(id < MAX_ENTS && "Entity out of range.");
  return name_sign[id];
}

inline void EntityMan::SetSignature(EntID id, const Signature &sign) {
  assert(id < MAX_ENTS && "Entity out of range.");
  name_sign[id] = sign;
}
