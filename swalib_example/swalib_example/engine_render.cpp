#include "engine_render.h"

#include "engine.h"
#include "stasis.h"

#include "core.h"
#include "font.h"
#include "stdafx.h"
#include "sys.h"
#include "vector2d.h"

#include "gameobject.h"
#include "sprite.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "transform.h"

#include "scene_01.h"

#include <vector>

static char buffer[256];
static float w = 0;
static float h = 0;

EngineRender EngineRender::instance;
EngineRender::EngineRender() {}
EngineRender &EngineRender::Get() { return instance; }

void EngineRender::Awake() {
  FONT_Init();

  // Save screen size as float
  w = (float)SCR_WIDTH;
  h = (float)SCR_HEIGHT;

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

  // Load textures
  SpriteLoader::LoadTextures();
}

void EngineRender::Start() {}

void EngineRender::Update() {
  // Render
  glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer to preset values.

  // Render background
  CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f),
                            vec2(1280.f, 720.f), SpriteLoader::sprBg.texture);

  // Render stuff
  for (auto &entity : Scene_01::GetRegistry()) {
    auto *tf = entity->GetComponent<Transform>();
    auto *go = entity->GetComponent<GameObject>();
    auto *sr = entity->GetComponent<SpriteRenderer>();
    auto *sa = entity->GetComponent<SpriteAnimation>();

    if (!tf || !go || !sr || !go->isActive)
      continue;

    // if (sa && sa->enabled && sa->animation) {
    if (sa) {

      auto &f2 = sa->count;
      auto f3 = sa->count;
      float &f4 = sa->count;
      float f5 = sa->count;

      auto &d2 = sa->duration;
      auto d3 = sa->duration;
      float &d4 = sa->duration;
      float d5 = sa->duration;

      auto &a2 = sa->animation;
      auto a3 = sa->animation;
      std::vector<Sprite> *a4 = sa->animation;
      std::vector<Sprite> a5 = *sa->animation;

      auto frameFreq = sa->duration / a3->size();

      // auto frame = (int)floorf(sa->count / frameFreq);

      // sr->sprite = &sa->animation->at(frame);

      // sa->count += (float)Stasis::GetTimeScaled() * 0.001f * sa->speed;
      // if (sa->count > sa->duration)
      //   sa->count -= sa->duration;
      float f6 = sa->count;
    }

    auto &pos = tf->position;
    auto &sze = sr->size;
    auto &uv0 = sr->sprite->uv0;
    auto &uv1 = sr->sprite->uv1;
    CORE_RenderCenteredSpriteWithUVs(vec2(pos.x, pos.y), vec2(sze.x, sze.y),
                                     vec2(uv0.x, uv0.y), vec2(uv1.x, uv1.y),
                                     sr->sprite->texture);
  }

  // Render balls
  // if (instance.balls != nullptr)
  //  for (auto &ball : *instance.balls) {
  //    Vec2 pos = ball->GetComponent<Transform>()->position;
  //    float r = ball->GetComponent<CircleCollider>()->radius;
  //    Vec2 rad = {r * 2.f, r * 2.f};
  //    GLuint tx = ball->GetComponent<SpriteRenderer>()->textureID;
  //    CORE_RenderCenteredSprite(vec2(pos.x, pos.y), vec2(rad.x, rad.y), tx);
  //  }

  // Render FPS and stuff
  sprintf(buffer, "TIME: %0.1f", Stasis::GetTimeScaled() / 1000.);
  FONT_DrawString({w * 0.05f, h * 0.9f}, buffer);

  SYS_Show(); // Exchanges the front and back buffers}
}

void EngineRender::Fixed() {}

void EngineRender::Quit() { FONT_End(); }
