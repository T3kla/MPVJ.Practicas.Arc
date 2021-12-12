#include "ass_03.h"
#include "engine.h"
#include <iostream>

int Main(void) {
  auto ass01 = Ass03();

  Engine::Run();

  return 0;
}

// https://austinmorlan.com/posts/entity_component_system/#the-entity-manager

// BALL LOGIC

// for (auto i = 0u; i < NUM_BALLS; i++) {
//   for (auto j = 0u; j < NUM_BALLS; j++) {
//     if (i == j)
//       continue;

//    auto limit = (balls[i].radius + balls[j].radius) *
//                 (balls[i].radius + balls[j].radius);

//    if (vlen2(balls[i].pos - balls[j].pos) <= limit) {
//      // Elastic sphere collisions
//      auto p1 = balls[i].pos;
//      auto p2 = balls[j].pos;
//      auto v1 = balls[i].vel;
//      auto v2 = balls[j].vel;
//      auto m1 = balls[i].mass;
//      auto m2 = balls[j].mass;
//      auto r1 = balls[i].radius;
//      auto r2 = balls[j].radius;

//      // Backtime to ensure single point intersection
//      auto backTimeRoot =
//          0.5f *
//          sqrtf(4.f * powf(p1.x * (v1.x - v2.x) + p2.x * (-v1.x + v2.x) +
//                               (p1.y - p2.y) * (v1.y - v2.y),
//                           2.f) -
//                4.f *
//                    (p1.x * p1.x + p1.y * p1.y - 2.f * p1.x * p2.x +
//                     p2.x * p2.x - 2.f * p1.y * p2.y + p2.y * p2.y - r1 * r1 -
//                     2.f * r1 * r2 - r2 * r2) *
//                    (v1.x * v1.x + v1.y * v1.y - 2.f * v1.x * v2.x +
//                     v2.x * v2.x - 2.f * v1.y * v2.y + v2.y * v2.y));
//      auto backTimeSummand = p1.x * v1.x - p2.x * v1.x + p1.y * v1.y -
//                             p2.y * v1.y - p1.x * v2.x + p2.x * v2.x -
//                             p1.y * v2.y + p2.y * v2.y;
//      auto backTimeDivisor = v1.x * v1.x + v1.y * v1.y - 2.f * v1.x * v2.x +
//                             v2.x * v2.x - 2.f * v1.y * v2.y + v2.y * v2.y;
//      auto backTime = (backTimeSummand + backTimeRoot) / backTimeDivisor;

//      if (isnan(backTimeSummand) || isnan(backTimeRoot) ||
//          isnan(backTimeDivisor)) {
//        continue;
//      }

//      backTime += 0.001f;

//      p1 -= v1 * backTime;
//      p2 -= v2 * backTime;

//      // Resolving collision
//      auto col_nor = vnorm(p1 - p2);

//      // Decompose to parallel and orthogonal components
//      auto v1_dot = vdot(col_nor, v1);
//      auto v1_par = col_nor * v1_dot;
//      auto v1_ort = v1 - v1_par;

//      auto v2_dot = vdot(col_nor, v2);
//      auto v2_par = col_nor * v2_dot;
//      auto v2_ort = v2 - v2_par;

//      // One dimensional collision with parallel component
//      auto v1_len = fabsf(v1_dot) * (v1_dot > 0.f ? 1.f : -1.f);
//      auto v2_len = fabsf(v2_dot) * (v2_dot > 0.f ? 1.f : -1.f);

//      // Conservation of momentum
//      auto rel_vel = 2.f * (m1 * v1_len + m2 * v2_len) / nozero(m1 + m2);

//      auto v1_len_f = rel_vel - v1_len;
//      auto v2_len_f = rel_vel - v2_len;

//      // Scale parallel component
//      v1_par *= v1_len_f / nozero(v1_len);
//      v2_par *= v2_len_f / nozero(v2_len);

//      // Recompose velocity
//      balls[i].vel = v1_par + v1_ort;
//      balls[j].vel = v2_par + v2_ort;

//      // Simple reflection, not enough!
//      //      auto nor = vnorm(balls[i].vel - balls[j].vel);
//      //      balls[i].vel = reflect(balls[i].vel, nor);
//      //      balls[j].vel = reflect(balls[j].vel, nor * -1.f);
//      break;
//    }
//  }

//  balls[i].pos = balls[i].pos + balls[i].vel * (float)(dt / 1000.);

//  // Rebound on margins
//  if ((balls[i].pos.x > SCR_WIDTH)) {
//    balls[i].pos.x = SCR_WIDTH - 1;
//    balls[i].vel.x *= -1.f;
//  }
//  if ((balls[i].pos.x < 0.f)) {
//    balls[i].pos.x = 1;
//    balls[i].vel.x *= -1.f;
//  }
//  if ((balls[i].pos.y > SCR_HEIGHT)) {
//    balls[i].pos.y = SCR_HEIGHT - 1;
//    balls[i].vel.y *= -1.f;
//  }
//  if ((balls[i].pos.y < 0.f)) {
//    balls[i].pos.y = 1;
//    balls[i].vel.y *= -1.f;
//  }
//}
