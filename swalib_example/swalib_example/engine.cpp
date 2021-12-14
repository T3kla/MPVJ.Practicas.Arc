#include "engine.h"
#include "engine_game.h"
#include "engine_input.h"
#include "engine_render.h"
#include "stasis.h"
#include "sys.h"

static double dt = 0.;
static double nowFx = 0.;
static double oldFx = 0.;
static double freqFx = 0.;

auto FreqRefresh = [](double &now, double &old, double &freq) {
  now = Stasis::GetTime();
  freq = now - old;
  old = now;
};

Engine Engine::instance;

Engine::Engine() {}

Engine &Engine::Get() { return instance; }

void Engine::Run() {
  Stasis::RefreshTime();

  EngineGame::Awake();
  EngineInput::Init();
  EngineRender::Init();
  EngineGame::Init();

  while (!SYS_GottaQuit()) {
    Stasis::RefreshTime();
    EngineInput::Loop();

    dt = Stasis::GetDelta();
    EngineGame::Update();

    instance.fxCount += dt;
    instance.fxCount = min(instance.fxCount, STEP * 2);
    while (instance.fxCount >= STEP) {
      FreqRefresh(nowFx, oldFx, freqFx);

      EngineGame::Fixed();

      instance.fxCount -= STEP;
    }

    EngineRender::Loop();
    SYS_Pump();
  }

  EngineInput::Exit();
  EngineGame::Exit();
  EngineRender::Exit();
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

float Engine::GetUpdateFPS() { return (float)(1000. / dt); }
float Engine::GetFixedFPS() { return (float)(1000. / freqFx); }
