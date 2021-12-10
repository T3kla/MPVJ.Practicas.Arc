#include "render.h"

#define LITE_GFX_IMPLEMENTATION

Render Render::instance;

Render::Render() {}

Render &Render::Get() { return instance; }

void Render::Init() {}

void Render::Loop() {}

void Render::Exit() {}
