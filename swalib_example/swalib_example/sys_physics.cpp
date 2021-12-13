#include "sys_physics.h"
#include "circle_collider.h"
#include "ecs_manager.h"
#include "rigidbody_2d.h"
#include "stasis.h"
#include "sys.h"
#include "transform_2d.h"
#include "vec.h"

inline void SysPhysics::Run() {
  auto nozero = [](const float &f) { return f == 0.f ? f + FLT_EPSILON : f; };
  auto &ecs = ECS::Get();

  for (auto const &a : entities) {
    auto &aTF = ecs.GetComponent<Transform2D>(a);
    auto &aRB = ecs.GetComponent<Rigidbody2D>(a);
    auto &aCC = ecs.GetComponent<CircleCollider>(a);
    for (auto const &b : entities) {
      if (a == b)
        continue;

      auto &bTF = ecs.GetComponent<Transform2D>(b);
      auto &bRB = ecs.GetComponent<Rigidbody2D>(b);
      auto &bCC = ecs.GetComponent<CircleCollider>(b);

      auto limit = (aCC.radius + bCC.radius) * (aCC.radius + bCC.radius);

      if ((aTF.position - bTF.position).MagnitudeSq() <= limit) {
        // Elastic sphere collisions
        auto p1 = aTF.position;
        auto p2 = bTF.position;
        auto v1 = aRB.velocity;
        auto v2 = bRB.velocity;
        auto m1 = aRB.mass;
        auto m2 = bRB.mass;
        auto r1 = aCC.radius;
        auto r2 = bCC.radius;

        // Backtime to ensure single point intersection
        auto backTimeRoot =
            0.5f *
            sqrtf(4.f * powf(p1.x * (v1.x - v2.x) + p2.x * (-v1.x + v2.x) +
                                 (p1.y - p2.y) * (v1.y - v2.y),
                             2.f) -
                  4.f *
                      (p1.x * p1.x + p1.y * p1.y - 2.f * p1.x * p2.x +
                       p2.x * p2.x - 2.f * p1.y * p2.y + p2.y * p2.y - r1 * r1 -
                       2.f * r1 * r2 - r2 * r2) *
                      (v1.x * v1.x + v1.y * v1.y - 2.f * v1.x * v2.x +
                       v2.x * v2.x - 2.f * v1.y * v2.y + v2.y * v2.y));
        auto backTimeSummand = p1.x * v1.x - p2.x * v1.x + p1.y * v1.y -
                               p2.y * v1.y - p1.x * v2.x + p2.x * v2.x -
                               p1.y * v2.y + p2.y * v2.y;
        auto backTimeDivisor = v1.x * v1.x + v1.y * v1.y - 2.f * v1.x * v2.x +
                               v2.x * v2.x - 2.f * v1.y * v2.y + v2.y * v2.y;
        auto backTime = (backTimeSummand + backTimeRoot) / backTimeDivisor;

        if (isnan(backTimeSummand) || isnan(backTimeRoot) ||
            isnan(backTimeDivisor)) {
          continue;
        }

        backTime += 0.001f;

        p1 -= v1 * backTime;
        p2 -= v2 * backTime;

        // Resolving collision
        auto col_nor = (p1 - p2).Normalized();

        // Decompose to parallel and orthogonal components
        auto v1_dot = Vec2::Dot(col_nor, v1);
        auto v1_par = col_nor * v1_dot;
        auto v1_ort = v1 - v1_par;

        auto v2_dot = Vec2::Dot(col_nor, v2);
        auto v2_par = col_nor * v2_dot;
        auto v2_ort = v2 - v2_par;

        // One dimensional collision with parallel component
        auto v1_len = fabsf(v1_dot) * (v1_dot > 0.f ? 1.f : -1.f);
        auto v2_len = fabsf(v2_dot) * (v2_dot > 0.f ? 1.f : -1.f);

        // Conservation of momentum
        auto rel_vel = 2.f * (m1 * v1_len + m2 * v2_len) / nozero(m1 + m2);

        auto v1_len_f = rel_vel - v1_len;
        auto v2_len_f = rel_vel - v2_len;

        // Scale parallel component
        v1_par *= v1_len_f / nozero(v1_len);
        v2_par *= v2_len_f / nozero(v2_len);

        // Recompose velocity
        aRB.velocity = v1_par + v1_ort;
        bRB.velocity = v2_par + v2_ort;

        break;
      }
    }

    aTF.position =
        aTF.position + aRB.velocity * (float)(Stasis::GetDelta() * 0.001);

    // Rebound on margins
    if (aTF.position.x > SCR_WIDTH) {
      aTF.position.x = SCR_WIDTH - 1;
      aRB.velocity.x *= -1.f;
    }
    if (aTF.position.x < 0.f) {
      aTF.position.x = 1;
      aRB.velocity.x *= -1.f;
    }
    if (aTF.position.y > SCR_HEIGHT) {
      aTF.position.y = SCR_HEIGHT - 1;
      aRB.velocity.y *= -1.f;
    }
    if (aTF.position.y < 0.f) {
      aTF.position.y = 1;
      aRB.velocity.y *= -1.f;
    }
  }
}
