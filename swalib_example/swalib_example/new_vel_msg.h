#pragma once

#include "msg.h"
#include "vec.h"

class NewVelMsg : public Msg {
public:
  NewVelMsg(Vec2 value = {0.f, 0.f});
  ~NewVelMsg();
  Vec2 newVel = {0.f, 0.f};
};
