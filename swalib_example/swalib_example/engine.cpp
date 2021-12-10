#include "engine.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "stasis.h"
#include "sys.h"

static double nowUp = 0.;
static double nowFx = 0.;
static double oldUp = 0.;
static double oldFx = 0.;
static double freqUp = 0.;
static double freqFx = 0.;

auto FreqRefresh = [](double &now, double &old, double &freq) {
  nowUp = Stasis::GetTime();
  freqUp = nowUp - oldUp;
  oldUp = nowUp;
};

Engine Engine::instance;

Engine::Engine() {}

Engine &Engine::Get() { return instance; }

void Engine::Run() {
  Stasis::RefreshTime();
  Input::Init();
  Render::Init();
  Game::Init();

  while (!SYS_GottaQuit()) {
    Stasis::RefreshTime();
    Input::Loop();

    FreqRefresh(nowUp, oldUp, freqUp);
    Game::Update();

    instance.fxCount += Stasis::GetDelta();
    instance.fxCount = min(instance.fxCount, STEP * 2);
    while (instance.fxCount >= STEP) {
      FreqRefresh(nowUp, oldUp, freqFx);
      Game::Fixed();

      instance.fxCount -= STEP;
    }

    Render::Loop();
    SYS_Pump();
  }

  Input::Exit();
  Game::Exit();
  Render::Exit();
}

Vec2 Engine::GetMousePos() {
  return Vec2((float)Get().mouseX, (float)Get().mouseY);
}

void Engine::SetMousePos(const Vec2 &pos) {
  Get().mouseX = pos.x;
  Get().mouseY = pos.y;
}

Vec2 Engine::GetMouseDelta() {
  return Vec2((float)Get().mouseDeltaX, (float)Get().mouseDeltaY);
}

void Engine::SetMouseDelta(const Vec2 &pos) {
  Get().mouseDeltaX = pos.x;
  Get().mouseDeltaY = pos.y;
}

float Engine::GetUpdateFPS() { return 1000. / freqUp; }
float Engine::GetFixedFPS() { return 1000. / freqFx; }
