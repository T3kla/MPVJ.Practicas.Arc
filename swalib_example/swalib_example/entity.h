#pragma once

using EntityID = unsigned long long;

class Entity {
private:
  EntityID id = 0;

public:
  virtual void EarlyUpdate() = 0; // Pre-component update
  virtual void Update() = 0;      // Post-component update
  virtual void LateUpdate() = 0;  // Post-Update update

  virtual EntityID GetEntityID() { return id; }
  virtual EntityID SetEntityID(const EntityID &id) { this->id = id; }
};
