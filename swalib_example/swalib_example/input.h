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
  static void Init();
  static void Loop();
  static void Exit();
};
