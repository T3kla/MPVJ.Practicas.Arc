#include "circle_collider.h"
#include "transform.h"

bool CircleCollider::IsColliding(std::vector<Entity *> *balls) {
  for (auto &ball : *balls) {
    auto &aTF = *owner->GetComponent<Transform>();
    auto &bTF = *ball->GetComponent<Transform>();

    auto &bCC = *ball->GetComponent<CircleCollider>();
    if ((aTF.position - bTF.position).MagnitudeSq() <=
        powf(radius + bCC.radius, 2))
      return true;
  }
  return false;
}
