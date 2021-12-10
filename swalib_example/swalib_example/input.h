#pragma once

class Input {
  friend class Engine;

private:                         // SINGLETON
  Input();                       //
  static Input instance;         //
public:                          //
  Input(const Input &) = delete; //
  static Input &Get();           //

private:
  void Init();
  void Loop();
  void Exit();
};
