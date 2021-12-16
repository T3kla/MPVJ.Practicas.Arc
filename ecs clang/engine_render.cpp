#include "engine_render.h"

EngineRender EngineRender::instance;
EngineRender::EngineRender() {}
EngineRender &EngineRender::Get() { return instance; };

void OnWindowResize(GLFWwindow *window, int w, int h) {
  EngineRender::SetWindowSize(w, h);
  lgfx_setup2d(w, h);
}

void EngineRender::GetWindowSize(int &width, int &height) {
  width = instance.width;
  height = instance.height;
}

void EngineRender::SetWindowSize(const int &width, const int &height) {
  instance.width = width;
  instance.height = height;
}

void EngineRender::Awake() {
  if (glfwInit() == 0)
    throw "Panic!";

  instance.window = glfwCreateWindow(800, 640, "", nullptr, nullptr);
  glfwMakeContextCurrent(instance.window);
  glfwSetInputMode(instance.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  glfwSetWindowSizeCallback(instance.window, OnWindowResize);

  glfwGetWindowSize(instance.window, &instance.width, &instance.height);
  lgfx_setup2d(instance.width, instance.height);
}
void EngineRender::Start() {}

void EngineRender::Update() {
  lgfx_clearcolorbuffer(0.1f, 0.1f, 0.1f);

  //   for (auto &&drawable : *Drawer::Get().GetDrawables())
  //     drawable->Draw();

  glfwSwapBuffers(instance.window);
}

void EngineRender::Fixed() {}

void EngineRender::Quit() {}
