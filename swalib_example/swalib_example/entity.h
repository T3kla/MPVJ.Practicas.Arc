#pragma once

#include "entity_manager.h"

class Entity {
private:
  EntID id = 0;
  Signature sign = Signature();

public:
  virtual void EarlyUpdate() = 0; // Pre-component update
  virtual void Update() = 0;      // Post-component update
  virtual void LateUpdate() = 0;  // Post-Update update

  virtual EntID GetEntityID() const { return id; }
  virtual void SetEntityID(const EntID &id) { this->id = id; }

  virtual Signature GetSignature() const { return sign; }
  virtual void SetSignature(const Signature &sign) { this->sign = sign; }
};
