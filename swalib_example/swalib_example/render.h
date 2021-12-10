#pragma once

#include "stdafx.h"

class Render {
  friend class Engine;

private:                           // SINGLETON
  Render();                        //
  static Render instance;          //
public:                            //
  Render(const Render &) = delete; //
  static Render &Get();            //

private:
  GLuint txBg = 0;
  GLuint txBall = 0;

  static void Init();
  static void Loop();
  static void Exit();

public:
  static const GLuint &GetTxBg();
  static const GLuint &GetTxBall();
};
