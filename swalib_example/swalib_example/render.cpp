#include "render.h"
#include "core.h"
#include "engine.h"
#include "font.h"
#include "stasis.h"
#include "sys.h"
#include "vector2d.h"

Render Render::instance;

Render::Render() {}

Render &Render::Get() { return instance; }

void Render::Init() {
  FONT_Init();

  // Load textures
  instance.txBg = CORE_LoadPNG("data/circle-bkg-128.png", true);
  instance.txBall = CORE_LoadPNG("data/tyrian_ball.png", false);

  // Set up rendering.
  //    Sets up clipping.
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
  //    Specifies clear values for the color buffers.
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  //    Specifies projection matrix is the current matrix.
  glMatrixMode(GL_PROJECTION);
  //    Replaces the current matrix with the identity matrix.
  glLoadIdentity();
  //    Multiplies the current matrix by an orthographic matrix.
  glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  //    Enabling two-dimensional texturing.
  glEnable(GL_TEXTURE_2D);

  // NOTA: Mirar diferencias comentando las 2 siguientes funciones.
  //    Blend the incoming RGBA color values with the values in
  //    the color buffers.
  glEnable(GL_BLEND);
  //	Blend func. for alpha color.
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::Loop() {
  // Render
  glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer to preset values.

  // Render background
  for (int i = 0; i <= SCR_WIDTH / 128; i++)
    for (int j = 0; j <= SCR_HEIGHT / 128; j++)
      CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f),
                                vec2(128.f, 128.f), instance.txBg);

  // Render balls
  /*for (int i = 0; i < NUM_BALLS; i++)
    CORE_RenderCenteredSprite(
        balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f),
        balls[i].gfx);*/

  auto avg_up_final = 0.0;
  auto avg_fx_final = 0.0;

  auto str_m1 = "       ARROW_UP AND ARROW_DOWN";
  auto str_m2 = "           TO MODIFY SCALE";

  FONT_DrawString(vec2(0, SCR_HEIGHT - 16), str_m1);
  FONT_DrawString(vec2(0, SCR_HEIGHT - 32), str_m2);

  auto str_sc = "       SCALE: " + std::to_string(Stasis::GetScale());
  auto str_tw =
      " SCALED TIME: " + std::to_string(Stasis::GetTimeScaled() / 1000.);
  auto str_tr = "   REAL TIME: " + std::to_string(Stasis::GetTime() / 1000.);
  auto str_up = "  UPDATE FPS: " + std::to_string(Engine::GetUpdateFPS());
  auto str_fx = "   FIXED FPS: " + std::to_string(Engine::GetFixedFPS());

  FONT_DrawString(vec2(0, 64), str_sc.c_str());
  FONT_DrawString(vec2(0, 48), str_tw.c_str());
  FONT_DrawString(vec2(0, 32), str_tr.c_str());
  FONT_DrawString(vec2(0, 16), str_fx.c_str());
  FONT_DrawString(vec2(0, 0), str_up.c_str());

  SYS_Show(); // Exchanges the front and back buffers}
}

void Render::Exit() {
  CORE_UnloadPNG(instance.txBg);
  CORE_UnloadPNG(instance.txBall);
  FONT_End();
}

const GLuint &Render::GetTxBg() { return instance.txBg; }
const GLuint &Render::GetTxBall() { return instance.txBall; }
