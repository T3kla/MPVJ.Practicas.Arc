#pragma once

#include "stdafx.h"
#include "sys_renderer.h"
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
  std::shared_ptr<SysRenderer> sysRenderer = nullptr;

  static void Init();
  static void Loop();
  static void Exit();

public:
  static const unsigned int &GetTxBg();
  static const unsigned int &GetTxBall();
};
