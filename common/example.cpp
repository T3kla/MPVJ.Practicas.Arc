#include "..\swalib_example\swalib_example\ball\ball.h"
#include "..\swalib_example\swalib_example\time\time.h"
#include "core.h"
#include "font.h"
#include "stdafx.h"
#include "sys.h"
#include "vector2d.h"
#include <iostream>

// Balls stuff
const float MAX_BALL_SPEED = 100.f; // Max vel. of ball. (pixels/second).
const unsigned int NUM_BALLS = 500; // Max. num balls.
const float MAX_BALL_RAD = 20.f;    //
const float MIN_BALL_RAD = 10.f;    //
Ball balls[NUM_BALLS];              // Array of balls.

// Time stuff
constexpr auto TIME_FIXED_FREQ = (1. / 60.) * 1000.;
constexpr auto TIME_AVG_SAMPLES = 64u;

auto avg_rl = std::vector<double>(TIME_AVG_SAMPLES, 0);
auto avg_fx = std::vector<double>(TIME_AVG_SAMPLES, 0);

auto tkl_time = tkl::time(3.0);

// Texture stuff
GLuint texbkg;
GLuint texsmallball;

void Init() {
  FONT_Init();

  // Load textures
  texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
  texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

  // Set up rendering.
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
  glClearColor(0.0f, 0.0f, 0.0f,
               0.0f); // Specifies clear values for the color buffers.
  glMatrixMode(
      GL_PROJECTION); // Specifies projection matrix is the current matrix.
  glLoadIdentity();   // Replaces the current matrix with the identity matrix.
  glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0,
          1.0); // Multiplies the current matrix by an orthographic matrix.
  glEnable(GL_TEXTURE_2D); // Enabling two-dimensional texturing.
  // NOTA: Mirar diferencias comentando las 2 siguientes funciones.
  glEnable(GL_BLEND); // Blend the incoming RGBA color values with the values in
                      // the color buffers.
  glBlendFunc(GL_SRC_ALPHA,
              GL_ONE_MINUS_SRC_ALPHA); // Blend func. for alpha color.

  // Init game state.
  for (int i = 0; i < NUM_BALLS; i++) {
    auto rad = CORE_FRand(MIN_BALL_RAD, MAX_BALL_RAD);
    auto mass = rad / 5.f;
    balls[i].pos =
        vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
    balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED),
                        CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
    balls[i].radius = CORE_FRand(MIN_BALL_RAD, MAX_BALL_RAD);
    balls[i].mass = mass;
    balls[i].gfx = texsmallball;
  }
}

void RenderLoop() {
  // Render
  glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer to preset values.

  // Render background
  for (int i = 0; i <= SCR_WIDTH / 128; i++)
    for (int j = 0; j <= SCR_HEIGHT / 128; j++)
      CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f),
                                vec2(128.f, 128.f), texbkg);

  // Render balls
  for (int i = 0; i < NUM_BALLS; i++)
    CORE_RenderCenteredSprite(
        balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f),
        balls[i].gfx);

  auto avg_up_final = 0.0;
  auto avg_fx_final = 0.0;

  for (auto &&i : avg_rl)
    avg_up_final += i;
  for (auto &&i : avg_fx)
    avg_fx_final += i;

  auto fps_up = (1.0 / (avg_up_final / (double)TIME_AVG_SAMPLES)) * 1000.0;
  auto fps_fx = (1.0 / (avg_fx_final / (double)TIME_AVG_SAMPLES)) * 1000.0;

  auto str_m1 = "       ARROW_UP AND ARROW_DOWN";
  auto str_m2 = "           TO MODIFY SCALE";

  FONT_DrawString(vec2(0, SCR_HEIGHT - 16), str_m1);
  FONT_DrawString(vec2(0, SCR_HEIGHT - 32), str_m2);

  auto str_sc = "       SCALE: " + std::to_string(tkl_time.get_scale());
  auto str_tw =
      " SCALED TIME: " + std::to_string(tkl_time.get_count_scaled() / 1000.0);
  auto str_tr =
      "   REAL TIME: " + std::to_string(tkl_time.get_count_unscaled() / 1000.0);
  auto str_up = "  UPDATE FPS: " + std::to_string(fps_up);
  auto str_fx = "   FIXED FPS: " + std::to_string(fps_fx);

  FONT_DrawString(vec2(0, 64), str_sc.c_str());
  FONT_DrawString(vec2(0, 48), str_tw.c_str());
  FONT_DrawString(vec2(0, 32), str_tr.c_str());
  FONT_DrawString(vec2(0, 16), str_fx.c_str());
  FONT_DrawString(vec2(0, 0), str_up.c_str());

  SYS_Show(); // Exchanges the front and back buffers
}

void GameLoop(double dt) {
  // auto reflect = [](const vec2 &vel, const vec2 &nor) { return vel - 2 *
  // (vdot(vel, nor)) * nor; };
  auto nozero = [](const float &f) { return f == 0.f ? f + FLT_EPSILON : f; };

  for (auto i = 0u; i < NUM_BALLS; i++) {
    for (auto j = 0u; j < NUM_BALLS; j++) {
      if (i == j)
        continue;

      auto limit = (balls[i].radius + balls[j].radius) *
                   (balls[i].radius + balls[j].radius);

      if (vlen2(balls[i].pos - balls[j].pos) <= limit) {
        // Elastic sphere collisions
        auto p1 = balls[i].pos;
        auto p2 = balls[j].pos;
        auto v1 = balls[i].vel;
        auto v2 = balls[j].vel;
        auto m1 = balls[i].mass;
        auto m2 = balls[j].mass;
        auto r1 = balls[i].radius;
        auto r2 = balls[j].radius;

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
        auto col_nor = vnorm(p1 - p2);

        // Decompose to parallel and orthogonal components
        auto v1_dot = vdot(col_nor, v1);
        auto v1_par = col_nor * v1_dot;
        auto v1_ort = v1 - v1_par;

        auto v2_dot = vdot(col_nor, v2);
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
        balls[i].vel = v1_par + v1_ort;
        balls[j].vel = v2_par + v2_ort;

        // Simple reflection, not enough!
        //      auto nor = vnorm(balls[i].vel - balls[j].vel);
        //      balls[i].vel = reflect(balls[i].vel, nor);
        //      balls[j].vel = reflect(balls[j].vel, nor * -1.f);
        break;
      }
    }

    balls[i].pos = balls[i].pos + balls[i].vel * (float)(dt / 1000.);

    // Rebound on margins
    if ((balls[i].pos.x > SCR_WIDTH)) {
      balls[i].pos.x = SCR_WIDTH - 1;
      balls[i].vel.x *= -1.f;
    }
    if ((balls[i].pos.x < 0.f)) {
      balls[i].pos.x = 1;
      balls[i].vel.x *= -1.f;
    }
    if ((balls[i].pos.y > SCR_HEIGHT)) {
      balls[i].pos.y = SCR_HEIGHT - 1;
      balls[i].vel.y *= -1.f;
    }
    if ((balls[i].pos.y < 0.f)) {
      balls[i].pos.y = 1;
      balls[i].vel.y *= -1.f;
    }
  }
}

void Input() {
  if (SYS_KeyPressed(SYS_KEY_UP))
    tkl_time.set_scale(tkl_time.get_scale() +
                       .001f * tkl_time.get_delta_unscaled());
  if (SYS_KeyPressed(SYS_KEY_DOWN))
    tkl_time.set_scale(tkl_time.get_scale() -
                       .001f * tkl_time.get_delta_unscaled());
}

void Update() { Input(); }

void FixedUpdate(double dt) {
  GameLoop(dt);
  RenderLoop();
}

void Loop() {
  auto next = [](auto &it) {
    it += 1u - TIME_AVG_SAMPLES * (it == TIME_AVG_SAMPLES - 1u);
  };
  auto cum_fx = 0.;
  auto avg_rl_it = 0u;
  auto avg_fx_it = 0u;

  while (!SYS_GottaQuit()) {
    tkl_time.update();

    auto delta = tkl_time.get_delta_unscaled();

    cum_fx += delta;
    avg_rl[avg_rl_it] = delta;
    next(avg_rl_it);

    Update();

    if (cum_fx >= TIME_FIXED_FREQ) {
      avg_fx[avg_fx_it] = cum_fx;
      next(avg_fx_it);

      FixedUpdate(cum_fx * tkl_time.get_scale());

      cum_fx = 0;
    }

    SYS_Pump();
  }
}

void Exit() {
  CORE_UnloadPNG(texbkg);
  CORE_UnloadPNG(texsmallball);
  FONT_End();
}

int Main(void) {
  Init();
  Loop();
  Exit();

  return 0;
}
