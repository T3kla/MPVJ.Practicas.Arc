#pragma once

class Render {
  friend class Engine;

private:                           // SINGLETON
  Render();                        //
  static Render instance;          //
public:                            //
  Render(const Render &) = delete; //
  static Render &Get();            //

private:
  void Init();
  void Loop();
  void Exit();
};
