#pragma once

// Component array which ensures static allocation
// and tight packaging of components

template <class T> class Juggler {
private:
  const T *;
  size_t capacity;
  size_t size;

public:
  Juggler(size_t capacity = 1);
  ~Juggler();

  size_t GetSize() { return size; };
  void SetSize(size_t size) { this->size = size; };

  size_t GetCapacity() { return capacity; };
  void SetCapacity(size_t capacity) { this->capacity = capacity; };
};
