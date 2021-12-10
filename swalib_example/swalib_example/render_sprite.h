#pragma once

#include "stdafx.h"

class RenderSprite {
private:
  GLuint texture = 0;

public:
  GLuint GetTexture() { return texture; }
  void SetTexture(GLuint texture) { this->texture = texture; }
};
