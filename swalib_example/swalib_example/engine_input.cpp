#include "engine_input.h"
#include "stasis.h"
#include "sys.h"
#include "vec.h"
#include <iostream>

static double x, y;

EngineInput EngineInput::instance;
EngineInput::EngineInput() {}
EngineInput &EngineInput::Get() { return instance; };

void EngineInput::Awake() {}

void EngineInput::Start() {}

void EngineInput::Update() {
  if (SYS_KeyPressed(SYS_KEY_UP))
    Stasis::SetScale(Stasis::GetScale() + .001 * Stasis::GetDelta());
  if (SYS_KeyPressed(SYS_KEY_DOWN))
    Stasis::SetScale(Stasis::GetScale() - .001 * Stasis::GetDelta());
}

void EngineInput::Fixed() {}

void EngineInput::Quit() {}

Vec2 EngineInput::GetMousePos() { return instance.mousePos; }
Vec2 EngineInput::GetMouseDelta() { return instance.mouseDelta; }
