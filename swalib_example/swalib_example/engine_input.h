#pragma once

class EngineInput {
  friend class Engine;

private:                                     // SINGLETON
  EngineInput();                             //
  static EngineInput instance;               //
public:                                      //
  EngineInput(const EngineInput &) = delete; //
  static EngineInput &Get();                 //

private:
  static void Init();
  static void Loop();
  static void Exit();
};
