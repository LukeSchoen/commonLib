#ifndef clCamera_h
#define clCamera_h

#include <stdbool.h>
#include <windows.h>
#include "clV3.h"

class clCamera
{
public:
  clV3 position;
  float yaw;
  float pitch;
  float moveSpeed;
  float mouseSensitivity;
  bool mouseCaptured;

  void init();
  void captureMouse(HWND hwnd, bool capture);
  void update(HWND hwnd, const bool *keys, float dt);
  void applyView();
};

#endif
