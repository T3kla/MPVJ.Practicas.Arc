#pragma once

#include "gameobject.h"
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

  std::vector<GameObject *> each = std::vector<GameObject *>();

public:
  static void Subscribe(GameObject *gameObject);
  static void UnSubscribe(const GameObject *gameObject);
  static const std::vector<GameObject *> *GetGameObjects();
};
