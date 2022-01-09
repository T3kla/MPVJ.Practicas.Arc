#pragma once

class Entity;
class Msg;

class Component {
public:
  Entity *owner = nullptr;
  virtual void Slot(){};
  virtual void ReceiveMessage(Msg *msg){};
};
