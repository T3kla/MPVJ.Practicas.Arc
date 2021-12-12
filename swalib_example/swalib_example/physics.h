#pragma once

#include "ecs_manager.h"
#include "system.h"

// Updates Collisions based on Collision components
// Updates Rigidbodies based on Collisions
// Update Transforms based on Rigidbodies velocity
//        ^^^^^^^^^^ only if it has RB

class SysPhysics : public System {
private:
public:
  void Run() {
    // for (auto const& entity : entities)
    //{
    //	auto& rigidBody = GetComponent<RigidBody>(entity);
    //	auto& transform = GetComponent<Transform>(entity);

    //	transform.position += rigidBody.velocity * dt;

    //	rigidBody.velocity += gravity.force * dt;
    //}
  }
};
