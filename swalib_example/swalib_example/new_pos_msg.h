#pragma once

#include "msg.h"
#include "vec.h"

class NewPosMsg : public Msg {
public:
  NewPosMsg(Vec2 value = {0.f, 0.f});
  ~NewPosMsg();
  Vec2 newPos = {0.f, 0.f};
};
