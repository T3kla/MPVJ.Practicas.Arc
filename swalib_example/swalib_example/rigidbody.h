#pragma once

#include "component.h"
#include "vec.h"

struct RigidBody : public Component {
  Vec2 velocity = {0.f, 0.f};
  float mass = 1.f;
  virtual void Slot() override {
    //     auto nozero = [](const float& f) { return f == 0.f ? f + FLT_EPSILON
    //     : f; };

    //    auto& aTF = *owner->GetComponent<Transform>();
    //    auto& aCC = *owner->GetComponent<CircleCollider>();

    //    for (auto& ball : *Practica::GetEntities()) {
    //        if (&ball == owner)
    //            continue; // TODO: test this

    //        auto& bTF = *ball.GetComponent<Transform>();
    //        auto& bRB = *ball.GetComponent<RigidBody>();
    //        auto& bCC = *ball.GetComponent<CircleCollider>();

    //        if ((aTF.position - bTF.position).MagnitudeSq() <=
    //            powf(aCC.radius + bCC.radius, 2)) {
    //            // Elastic sphere collisions
    //            auto p1 = aTF.position;
    //            auto p2 = bTF.position;
    //            auto v1 = velocity;
    //            auto v2 = bRB.velocity;
    //            auto m1 = mass;
    //            auto m2 = bRB.mass;
    //            auto r1 = aCC.radius;
    //            auto r2 = bCC.radius;

    //            // Backtime to ensure single point intersection
    //            auto backTimeRoot =
    //                0.5f *
    //                sqrtf(4.f * powf(p1.x * (v1.x - v2.x) + p2.x * (-v1.x +
    //                v2.x) +
    //                    (p1.y - p2.y) * (v1.y - v2.y),
    //                    2.f) -
    //                    4.f *
    //                    (p1.x * p1.x + p1.y * p1.y - 2.f * p1.x * p2.x +
    //                        p2.x * p2.x - 2.f * p1.y * p2.y + p2.y * p2.y - r1
    //                        * r1 - 2.f * r1 * r2 - r2 * r2) *
    //                    (v1.x * v1.x + v1.y * v1.y - 2.f * v1.x * v2.x +
    //                        v2.x * v2.x - 2.f * v1.y * v2.y + v2.y * v2.y));
    //            auto backTimeSummand = p1.x * v1.x - p2.x * v1.x + p1.y * v1.y
    //            -
    //                p2.y * v1.y - p1.x * v2.x + p2.x * v2.x -
    //                p1.y * v2.y + p2.y * v2.y;
    //            auto backTimeDivisor = v1.x * v1.x + v1.y * v1.y - 2.f * v1.x
    //            * v2.x +
    //                v2.x * v2.x - 2.f * v1.y * v2.y + v2.y * v2.y;
    //            auto backTime = (backTimeSummand + backTimeRoot) /
    //            backTimeDivisor;

    //            if (isnan(backTimeSummand) || isnan(backTimeRoot) ||
    //                isnan(backTimeDivisor)) {
    //                continue;
    //            }

    //            backTime += 0.001f;

    //            p1 -= v1 * backTime;
    //            p2 -= v2 * backTime;

    //            // Resolving collision
    //            auto col_nor = (p1 - p2).Normalized();

    //            // Decompose to parallel and orthogonal components
    //            auto v1_dot = Vec2::Dot(col_nor, v1);
    //            auto v1_par = col_nor * v1_dot;
    //            auto v1_ort = v1 - v1_par;

    //            auto v2_dot = Vec2::Dot(col_nor, v2);
    //            auto v2_par = col_nor * v2_dot;
    //            auto v2_ort = v2 - v2_par;

    //            // One dimensional collision with parallel component
    //            auto v1_len = fabsf(v1_dot) * (v1_dot > 0.f ? 1.f : -1.f);
    //            auto v2_len = fabsf(v2_dot) * (v2_dot > 0.f ? 1.f : -1.f);

    //            // Conservation of momentum
    //            auto rel_vel = 2.f * (m1 * v1_len + m2 * v2_len) / nozero(m1 +
    //            m2);

    //            auto v1_len_f = rel_vel - v1_len;
    //            auto v2_len_f = rel_vel - v2_len;

    //            // Scale parallel component
    //            v1_par *= v1_len_f / nozero(v1_len);
    //            v2_par *= v2_len_f / nozero(v2_len);

    //            // Recompose velocity
    //            velocity = v1_par + v1_ort;
    //            bRB.velocity = v2_par + v2_ort;

    //            break;
    //        }
    //    }

    //    aTF.position += velocity * (float)(Stasis::GetDeltaScaled() / 1000.);

    //    // Rebound on margins
    //    if ((aTF.position.x > SCR_WIDTH)) {
    //        aTF.position.x = SCR_WIDTH - 1;
    //        velocity.x *= -1.f;
    //    }
    //    if ((aTF.position.x < 0.f)) {
    //        aTF.position.x = 1;
    //        velocity.x *= -1.f;
    //    }
    //    if ((aTF.position.y > SCR_HEIGHT)) {
    //        aTF.position.y = SCR_HEIGHT - 1;
    //        velocity.y *= -1.f;
    //    }
    //    if ((aTF.position.y < 0.f)) {
    //        aTF.position.y = 1;
    //        velocity.y *= -1.f;
    //    }
  }
};
