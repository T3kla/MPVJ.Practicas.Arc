#include "entity_manager.h"
#include <cassert>

EntityMan::EntityMan() {
  for (EntID i = 0; i < MAX_ENTS; ++i)
    unusedIDs.push(i);
}

EntID EntityMan::BorrowID() {
  assert(count < MAX_ENTS && "Too many entities in existence.");

  EntID id = unusedIDs.front();
  unusedIDs.pop();
  ++count;

  return id;
}

void EntityMan::ReturnID(EntID id) {
  assert(id < MAX_ENTS && "Entity out of range.");

  name_sign[id].reset();

  unusedIDs.push(id);
  --count;
}

const Signature &EntityMan::GetSignature(EntID id) const {
  assert(id < MAX_ENTS && "Entity out of range.");
  return name_sign[id];
}

void EntityMan::SetSignature(EntID id, const Signature &sign) {
  assert(id < MAX_ENTS && "Entity out of range.");
  name_sign[id] = sign;
}
