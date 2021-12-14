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
  std::vector<GameObject *> each = std::vector<GameObject *>();

  static void Init();
  static void Exit();

  static void Awake();  // GameObject calls
  static void Start();  //
  static void Update(); //
  static void Fixed();  //
  static void End();    //

public:
  static void Subscribe(GameObject *gameObject);
  static void UnSubscribe(const GameObject *gameObject);
  static const std::vector<GameObject *> *GetGameObjects();
};
