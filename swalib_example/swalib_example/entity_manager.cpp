#include "entity_manager.h"

EntityMan::EntityMan() {
  for (EntID i = 0; i < MAX_ENTS; ++i)
    unusedIDs.push(i);
}

EntID EntityMan::BorrowID() {
  if (count > MAX_ENTS)
    throw "Too many entities in existence.";

  EntID id = unusedIDs.front();
  unusedIDs.pop();
  ++count;

  return id;
}

void EntityMan::ReturnID(EntID id) {
  if (id > MAX_ENTS)
    throw "Entity out of range.";

  name_sign[id].reset();

  unusedIDs.push(id);
  --count;
}

const Signature &EntityMan::GetSignature(EntID id) const {
  if (id > MAX_ENTS)
    throw "Entity out of range.";
  return name_sign[id];
}

void EntityMan::SetSignature(EntID id, const Signature &sign) {
  if (id > MAX_ENTS)
    throw "Entity out of range.";
  name_sign[id] = sign;
}
