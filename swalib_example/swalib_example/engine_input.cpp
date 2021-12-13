#include "engine_input.h"
#include "engine.h"
#include "engine_render.h"
#include "stasis.h"
#include "sys.h"
#include "vec.h"
#include <iostream>

EngineInput EngineInput::instance;

EngineInput::EngineInput() {}

EngineInput &EngineInput::Get() { return instance; }

void EngineInput::Init() {}

void EngineInput::Loop() {
  if (SYS_KeyPressed(SYS_KEY_UP))
    Stasis::SetScale(Stasis::GetScale() + .001 * Stasis::GetDelta());
  if (SYS_KeyPressed(SYS_KEY_DOWN))
    Stasis::SetScale(Stasis::GetScale() - .001 * Stasis::GetDelta());
}

void EngineInput::Exit() {}
