#include <math.h>

#include "renderer.h"
#include "gl_api.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static float deg_to_rad(float d)
{
  return d * (float)(M_PI / 180.0);
}

Renderer::Renderer()
{
}

void Renderer::beginFrame(int width, int height)
{
  glViewport(0, 0, width, height);
  glClearColor(0.08f, 0.09f, 0.12f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setPerspective(float fovYDeg, float aspect, float zNear, float zFar)
{
  float fovRad = deg_to_rad(fovYDeg);
  float top = tanf(fovRad * 0.5f) * zNear;
  float right = top * aspect;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-right, right, -top, top, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
}

void Renderer::applyCamera(clCamera *camera)
{
  clCamera c = *camera;
  c.applyView();
}
