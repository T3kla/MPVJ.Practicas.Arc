#pragma once

#include "component.h"
#include "new_pos_msg.h"
#include "vec.h"

struct Transform : public Component {
  Vec2 position = {0.f, 0.f};

  virtual void Slot() override{};

  virtual void ReceiveMessage(Msg *msg) override {
    auto *ptr = dynamic_cast<NewPosMsg *>(msg);
    if (ptr != nullptr)
      position = ptr->newPos;
  }
};
