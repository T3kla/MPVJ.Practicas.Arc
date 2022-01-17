#pragma once

struct Player {
  int health = 15;
  float speed = 100.f;
  char *state = nullptr;
  bool reversed = false;
};
