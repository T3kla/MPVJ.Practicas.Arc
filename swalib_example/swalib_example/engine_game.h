#pragma once

#include "object.h"
#include <vector>

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

  std::vector<Object *> each = std::vector<Object *>();

public:
  static void Subscribe(Object *gameObject);
  static void UnSubscribe(const Object *gameObject);
  static const std::vector<Object *> *GetGameObjects();
};
