#include "engine.h"

#include "engine_game.h"
#include "engine_input.h"
#include "engine_render.h"
#include "stasis.h"

static double fxCount = 0.;

Engine Engine::instance;
Engine::Engine() {}
Engine &Engine::Get() { return instance; };

void Engine::Run() {
  Stasis::RefreshTime();

  EngineInput::Awake();
  EngineGame::Awake();
  EngineRender::Awake();

  EngineInput::Start();
  EngineGame::Start();
  EngineRender::Start();

  while (!glfwWindowShouldClose(EngineRender::GetWindow())) {
    Stasis::RefreshTime();

    EngineInput::Update();
    EngineGame::Update();

    fxCount += Stasis::GetDelta();
    fxCount = min(fxCount, STP * 2.);
    while (fxCount >= STP) {
      EngineInput::Fixed();
      EngineGame::Fixed();
      EngineRender::Fixed();
      fxCount -= STP;
    }

    EngineRender::Update();
  }

  EngineInput::Quit();
  EngineGame::Quit();
  EngineRender::Quit();
}
