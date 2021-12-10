#include "input.h"
#include "engine.h"
#include "render.h"
#include "vec.h"
#include <iostream>

Input Input::instance;

Input::Input() {}

Input &Input::Get() { return instance; }

void Input::Init() {}

void Input::Loop() {}

void Input::Exit() {}
