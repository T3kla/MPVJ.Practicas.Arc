#pragma once

class Entity;

struct Component {
  Entity *owner = nullptr;
};
