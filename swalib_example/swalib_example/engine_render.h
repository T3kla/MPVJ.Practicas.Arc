#pragma once

#include "ball.h"
#include "stdafx.h"
#include <memory>

class EngineRender {
  friend class Engine;

private:                                       // SINGLETON
  EngineRender();                              //
  static EngineRender instance;                //
public:                                        //
  EngineRender(const EngineRender &) = delete; //
  static EngineRender &Get();                  //

private:
  GLuint txBg = 0;
  GLuint txBall = 0;

  std::vector<Ball> *balls = nullptr;

  static void Awake();
  static void Start();
  static void Update();
  static void Fixed();
  static void Quit();

public:
  static const unsigned int &GetTxBg();
  static const unsigned int &GetTxBall();

  static void SetBallVector(std::vector<Ball> *balls);
};
