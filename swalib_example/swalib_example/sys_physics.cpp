#include "sys_physics.h"
#include "circle_collider.h"
#include "ecs_manager.h"
#include "entity_manager.h"
#include "rigidbody_2d.h"
#include "stasis.h"
#include "sys.h"
#include "transform_2d.h"
#include "vec.h"

static std::vector<Transform2D> tf;
static std::vector<Rigidbody2D> rb;

void SysPhysics::Run() {
  auto nozero = [](const float &f) { return f == 0.f ? f + FLT_EPSILON : f; };
  auto &ecs = ECS::Get();

  // Buffer up
  tf.clear();
  rb.clear();
  for (auto const &ent : entities) {
    tf.emplace_back(ecs.GetComponent<Transform2D>(ent));
    rb.emplace_back(ecs.GetComponent<Rigidbody2D>(ent));
  }

  // Calculate collisions
  for (size_t i = 0; i < entities.size(); i++) {
    for (size_t j = 0; j < entities.size(); j++) {
      if (i == j)
        continue;

      if ((tf[i].position - tf[j].position).MagnitudeSq() <=
          powf(tf[i].scale.x + tf[j].scale.x, 2)) {
        // Elastic sphere collisions
        auto &p1 = tf[i].position;
        auto &p2 = tf[j].position;
        auto &v1 = rb[i].velocity;
        auto &v2 = rb[j].velocity;
        auto &m1 = rb[i].mass;
        auto &m2 = rb[j].mass;
        auto &r1 = tf[i].scale.x;
        auto &r2 = tf[j].scale.x;

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
        rb[i].velocity = v1_par + v1_ort;
        rb[j].velocity = v2_par + v2_ort;

        break;
      }
    }

    tf[i].position = tf[i].position +
                     rb[i].velocity * (float)(Stasis::GetDeltaScaled() * 0.001);

    // Rebound on margins
    if (tf[i].position.x > SCR_WIDTH) {
      tf[i].position.x = SCR_WIDTH - 1;
      rb[i].velocity.x *= -1.f;
    }
    if (tf[i].position.x < 0.f) {
      tf[i].position.x = 1;
      rb[i].velocity.x *= -1.f;
    }
    if (tf[i].position.y > SCR_HEIGHT) {
      tf[i].position.y = SCR_HEIGHT - 1;
      rb[i].velocity.y *= -1.f;
    }
    if (tf[i].position.y < 0.f) {
      tf[i].position.y = 1;
      rb[i].velocity.y *= -1.f;
    }
  }

  // Buffer down
  size_t count = 0;
  for (auto it = entities.begin(); it != entities.end(); ++it) {
    ecs.GetComponent<Transform2D>(*it) = tf[count];
    ecs.GetComponent<Rigidbody2D>(*it) = rb[count];
    count++;
  }
}
