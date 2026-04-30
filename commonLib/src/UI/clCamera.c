#include <math.h>

#include "clCamera.h"
#include "gl_api.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static float deg_to_rad(float d)
{
  return d * (float)(M_PI / 180.0);
}

static clV3 v3_from(float x, float y, float z)
{
  clV3 v;
  v.set(x, y, z);
  return v;
}

static clV3 v3_add_local(clV3 a, clV3 b)
{
  return v3_from(a.x + b.x, a.y + b.y, a.z + b.z);
}

static clV3 v3_sub_local(clV3 a, clV3 b)
{
  return v3_from(a.x - b.x, a.y - b.y, a.z - b.z);
}

static clV3 v3_scale_local(clV3 a, float s)
{
  return v3_from(a.x *s, a.y *s, a.z *s);
}

static float v3_len_local(clV3 a)
{
  return sqrtf(a.x *a.x + a.y *a.y + a.z *a.z);
}

static clV3 v3_norm_local(clV3 a)
{
  float l = v3_len_local(a);
  if (l <= 0.00001f)
    return v3_from(0.0f, 0.0f, 0.0f);
  return v3_scale_local(a, 1.0f / l);
}

static clV3 v3_cross_local(clV3 a, clV3 b)
{
  return v3_from(
           a.y *b.z - a.z *b.y,
           a.z *b.x - a.x *b.z,
           a.x *b.y - a.y *b.x
         );
}

static void set_cursor_visible(bool visible)
{
  int count = ShowCursor(visible);
  int guard = 0;

  while (guard < 16)
  {
    if (visible && count >= 0)
      break;
    if (!visible && count < 0)
      break;
    count = ShowCursor(visible);
    ++guard;
  }
}

void clCamera::init()
{
  this->position.set(0.0f, 1.5f, 8.0f);
  this->yaw = -90.0f;
  this->pitch = 0.0f;
  this->moveSpeed = 5.0f;
  this->mouseSensitivity = 0.08f;
  this->mouseCaptured = false;
}

void clCamera::captureMouse(HWND hwnd, bool capture)
{
  this->mouseCaptured = capture;
  set_cursor_visible(!capture);

  if (capture)
  {
    RECT r;
    GetClientRect(hwnd, &r);
    POINT center = {(r.right - r.left) / 2, (r.bottom - r.top) / 2};
    ClientToScreen(hwnd, &center);
    SetCursorPos(center.x, center.y);
  }
}

void clCamera::update(HWND hwnd, const bool *keys, float dt)
{
  if (this->mouseCaptured)
  {
    RECT r;
    GetClientRect(hwnd, &r);

    POINT center = {(r.right - r.left) / 2, (r.bottom - r.top) / 2};
    POINT screenCenter = center;
    ClientToScreen(hwnd, &screenCenter);

    POINT p;
    GetCursorPos(&p);

    float dx = (float)(p.x - screenCenter.x);
    float dy = (float)(p.y - screenCenter.y);

    this->yaw += dx * this->mouseSensitivity;
    this->pitch -= dy * this->mouseSensitivity;

    if (this->pitch > 89.0f)
      this->pitch = 89.0f;
    if (this->pitch < -89.0f)
      this->pitch = -89.0f;

    SetCursorPos(screenCenter.x, screenCenter.y);
  }

  float yawRad = deg_to_rad(this->yaw);
  float pitchRad = deg_to_rad(this->pitch);

  clV3 forward;
  forward.set(
           cosf(yawRad) * cosf(pitchRad),
           sinf(pitchRad),
           sinf(yawRad) * cosf(pitchRad)
         );
  forward = v3_norm_local(forward);

  clV3 flatForward;
  flatForward.set(forward.x, 0.0f, forward.z);
  flatForward = v3_norm_local(flatForward);

  clV3 right;
  right.set(
         flatForward.y * 0.0f - flatForward.z * 1.0f,
         flatForward.z * 0.0f - flatForward.x * 0.0f,
         flatForward.x * 1.0f - flatForward.y * 0.0f
       );
  right = v3_norm_local(right);

  clV3 move;

  if (keys['W'])
    move = v3_add_local(move, flatForward);
  if (keys['S'])
    move = v3_sub_local(move, flatForward);
  if (keys['D'])
    move = v3_add_local(move, right);
  if (keys['A'])
    move = v3_sub_local(move, right);
  if (keys[VK_SPACE])
    move.y += 1.0f;
  if (keys[VK_CONTROL])
    move.y -= 1.0f;

  if (v3_len_local(move) > 0.0f)
  {
    move = v3_norm_local(move);
    move = v3_scale_local(move, this->moveSpeed *dt);
    this->position = v3_add_local(this->position, move);
  }
}

void clCamera::applyView()
{
  float yawRad = deg_to_rad(this->yaw);
  float pitchRad = deg_to_rad(this->pitch);

  clV3 forward;
  forward.set(
           cosf(yawRad) * cosf(pitchRad),
           sinf(pitchRad),
           sinf(yawRad) * cosf(pitchRad)
         );
  forward = v3_norm_local(forward);

  clV3 right;
  right.set(
         forward.y * 0.0f - forward.z * 1.0f,
         forward.z * 0.0f - forward.x * 0.0f,
         forward.x * 1.0f - forward.y * 0.0f
       );
  right = v3_norm_local(right);
  clV3 up;
  up.set(
      right.y *forward.z - right.z *forward.y,
      right.z *forward.x - right.x *forward.z,
      right.x *forward.y - right.y *forward.x
    );

  GLfloat m[16] =
  {
    right.x, up.x, -forward.x, 0.0f,
    right.y, up.y, -forward.y, 0.0f,
    right.z, up.z, -forward.z, 0.0f,
    0.0f,    0.0f,  0.0f,      1.0f
  };

  glLoadIdentity();
  glMultMatrixf(m);
  glTranslatef(-this->position.x, -this->position.y, -this->position.z);
}
