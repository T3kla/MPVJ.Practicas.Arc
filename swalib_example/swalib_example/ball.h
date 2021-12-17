#pragma once

#include "stdafx.h"
#include "vec.h"
#include <vector>

class Ball {
private:
  Vec2 position;
  Vec2 velocity;
  GLuint texture;
  float radius;
  float mass;

public:
  Ball(const Vec2 &position = {0.f, 0.f}, const Vec2 &velocity = {0.f, 0.f},
       const GLuint &texture = 0, const float &radius = 0.f,
       const float &mass = 0.f);
  Ball(const Ball &ball);
  ~Ball();

  Vec2 GetPosition();
  void SetPosition(Vec2 position);

  Vec2 GetVelocity();
  void SetVelocity(Vec2 velocity);

  GLuint GetTextureID();
  void SetTextureID(GLuint texture);

  float GetRadius();
  void SetRadius(float radius);

  float GetMass();
  void SetMass(float mass);

  void Slot(std::vector<Ball> *balls);
  bool IsColliding(std::vector<Ball> *balls);
};
