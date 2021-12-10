#include "input.h"
#include "engine.h"
#include "render.h"
#include "stasis.h"
#include "sys.h"
#include "vec.h"
#include <iostream>

Input Input::instance;

Input::Input() {}

Input &Input::Get() { return instance; }

void Input::Init() {}

void Input::Loop() {
  if (SYS_KeyPressed(SYS_KEY_UP))
    Stasis::SetScale(Stasis::GetScale() + .001 * Stasis::GetDelta());
  if (SYS_KeyPressed(SYS_KEY_DOWN))
    Stasis::SetScale(Stasis::GetScale() - .001 * Stasis::GetDelta());
}

void Input::Exit() {}
