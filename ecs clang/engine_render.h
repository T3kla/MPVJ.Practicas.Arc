#pragma once

#include "glfw3.h"
#include "litegfx.h"
#include "stb_image.h"

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

class EngineRender {
  friend class Engine;

private:                                       // SINGLETON
  EngineRender();                              //
  static EngineRender instance;                //
public:                                        //
  EngineRender(const EngineRender &) = delete; //
  static EngineRender &Get();                  //

private:
  GLFWwindow *window;
  int width;
  int height;

  static void Awake();
  static void Start();
  static void Update();
  static void Fixed();
  static void Quit();

public:
  static GLFWwindow *GetWindow();
  static void GetWindowSize(int &width, int &height);
  static void SetWindowSize(const int &width, const int &height);
};
