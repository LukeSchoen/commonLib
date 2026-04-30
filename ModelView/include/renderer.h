#ifndef RENDERER_H
#define RENDERER_H

#include "clCamera.h"

class Renderer
{
public:
  Renderer();

  void beginFrame(int width, int height);
  void setPerspective(float fovYDeg, float aspect, float zNear, float zFar);
  void applyCamera(clCamera *camera);
};

#endif
