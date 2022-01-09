#include "circle_collider.h"
#include "transform.h"

bool CircleCollider::AreColliding(const Transform &aTF,
                                  const CircleCollider &aCC,
                                  const Transform &bTF,
                                  const CircleCollider &bCC) {
  if ((aTF.position - bTF.position).MagnitudeSq() <=
      powf(aCC.radius + bCC.radius, 2))
    return true;
  else
    return false;
}

bool CircleCollider::AnyOverlap(const Transform &tf, const CircleCollider &cc,
                                std::vector<Entity *> balls) {

  for (auto &ball : balls) {
    auto &bTF = *ball->GetComponent<Transform>();
    auto &bCC = *ball->GetComponent<CircleCollider>();

    if (AreColliding(tf, cc, bTF, bCC))
      return true;
  }
  return false;
}
