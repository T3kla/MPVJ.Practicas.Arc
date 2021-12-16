#pragma once

class EngineGame {
  friend class Engine;

private:                                   // SINGLETON
  EngineGame();                            //
  static EngineGame instance;              //
public:                                    //
  EngineGame(const EngineGame &) = delete; //
  static EngineGame &Get();                //

private:
  static void Awake();
  static void Start();
  static void Update();
  static void Fixed();
  static void Quit();
};
