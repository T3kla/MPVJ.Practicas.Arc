#include "engine_input.h"
#include "engine_render.h"

static double x, y;

EngineInput EngineInput::instance;
EngineInput::EngineInput() {}
EngineInput &EngineInput::Get() { return instance; };

void EngineInput::Awake() {}

void EngineInput::Start() {}

void EngineInput::Update() {
  glfwPollEvents();
  auto *window = EngineRender::GetWindow();

  // Update mouse pos
  glfwGetCursorPos(window, &x, &y);
  auto newPos = Vec2((float)x, (float)y);
  instance.mouseDelta = instance.mousePos - newPos;
  instance.mousePos = newPos;

  // Exit
  if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, 1);
}

void EngineInput::Fixed() {}

void EngineInput::Quit() { glfwTerminate(); }

Vec2 EngineInput::GetMousePos() { return instance.mousePos; }
Vec2 EngineInput::GetMouseDelta() { return instance.mouseDelta; }
