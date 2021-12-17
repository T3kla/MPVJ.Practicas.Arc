#include "engine.h"
#include "practica.h"
#include <iostream>

int Main(void) {

  // FPS lock   en engine.h
  // BALLS_NUM  en practica.h
  // MAX_SPEED  en practica.h
  // MAX_RADIUS en practica.h
  // MIN_RADIUS en practica.h

  auto prtc = Practica();
  Engine::Run();

  return 0;
}
