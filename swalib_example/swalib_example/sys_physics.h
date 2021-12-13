#pragma once

#include "system.h"

// Updates Collisions based on Collision components
// Updates Rigidbodies based on Collisions
// Update Transforms based on Rigidbodies velocity
//        ^^^^^^^^^^ only if it has RB

class SysPhysics : public System {
public:
  void Run();
};
