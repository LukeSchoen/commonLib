#include <windows.h>
#include <stdbool.h>
#include "clRenderObject.h"
#include "clString.h"
#include "gl_api.h"
#include "clMesh.h"
#include "clCamera.h"
#include "renderer.h"

class AppState
{
public:
  bool running;
  bool keys[256];
  int width;
  int height;

  Renderer renderer;
  clCamera camera;

  clMesh groundMesh;
  clMesh cubeRed;
  clMesh cubeBlue;
  clMesh cubeGreen;
  clMesh cubeGold;
  clMesh cubePurple;

  clRenderObject ground;
  clRenderObject cubes[5];

  LARGE_INTEGER freq;
  LARGE_INTEGER prevTime;
};

static AppState g_app;

static void app_init(AppState *app)
{
  app->running = true;
  ZeroMemory(app->keys, sizeof(app->keys));
  app->width = 1280;
  app->height = 720;

  app->camera.init();

  clV3 colorGround; colorGround.set(0.25f, 0.25f, 0.25f);
  clV3 colorRed; colorRed.set(0.95f, 0.25f, 0.25f);
  clV3 colorBlue; colorBlue.set(0.20f, 0.70f, 0.95f);
  clV3 colorGreen; colorGreen.set(0.25f, 0.90f, 0.30f);
  clV3 colorGold; colorGold.set(0.95f, 0.80f, 0.25f);
  clV3 colorPurple; colorPurple.set(0.75f, 0.30f, 0.90f);

  app->groundMesh.initGrid(20, colorGround);
  app->cubeRed.initCube(1.5f, colorRed);
  app->cubeBlue.initCube(1.5f, colorBlue);
  app->cubeGreen.initCube(1.5f, colorGreen);
  app->cubeGold.initCube(1.0f, colorGold);
  app->cubePurple.initCube(1.0f, colorPurple);

  clV3 posGround; posGround.set(0.0f, 0.0f, 0.0f);
  clV3 pos0; pos0.set(0.0f, 1.0f, 0.0f);
  clV3 pos1; pos1.set(3.0f, 1.0f, -2.0f);
  clV3 pos2; pos2.set(-3.0f, 1.0f, -3.0f);
  clV3 pos3; pos3.set(2.0f, 2.5f, 3.0f);
  clV3 pos4; pos4.set(-4.5f, 0.75f, 2.0f);

  app->ground.init(&app->groundMesh, posGround);
  app->cubes[0].init(&app->cubeRed, pos0);
  app->cubes[1].init(&app->cubeBlue, pos1);
  app->cubes[2].init(&app->cubeGreen, pos2);
  app->cubes[3].init(&app->cubeGold, pos3);
  app->cubes[4].init(&app->cubePurple, pos4);
}

static void app_render(AppState *app)
{
  app->renderer.beginFrame(app->width, app->height);

  float aspect = (app->height == 0) ? 1.0f : (float)app->width / (float)app->height;
  app->renderer.setPerspective(70.0f, aspect, 0.1f, 200.0f);
  app->renderer.applyCamera(&app->camera);

  app->ground.draw();

  for (int i = 0; i < 5; ++i)
    app->cubes[i].draw();
}

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_DESTROY:
    g_app.running = false;
    PostQuitMessage(0);
    return 0;

  case WM_SIZE:
    g_app.width = LOWORD(lParam);
    g_app.height = HIWORD(lParam);
    return 0;

  case WM_SETFOCUS:
    g_app.camera.captureMouse(hwnd, true);
    return 0;

  case WM_KILLFOCUS:
    g_app.camera.captureMouse(hwnd, false);
    ZeroMemory(g_app.keys, sizeof(g_app.keys));
    return 0;

  case WM_KEYDOWN:
    if (wParam < 256)
      g_app.keys[wParam] = true;
    if (wParam == VK_ESCAPE)
    {
      g_app.running = false;
      DestroyWindow(hwnd);
    }
    return 0;

  case WM_KEYUP:
    if (wParam < 256)
      g_app.keys[wParam] = false;
    return 0;

  case WM_RBUTTONDOWN:
    g_app.camera.captureMouse(hwnd, !g_app.camera.mouseCaptured);
    return 0;

  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  (void)hPrevInstance;
  (void)lpCmdLine;

  app_init(&g_app);

  WNDCLASS wc;
  ZeroMemory(&wc, sizeof(wc));
  wc.style = CS_OWNDC;
  wc.lpfnWndProc = wnd_proc;
  wc.hInstance = hInstance;

  clString test("OpenGL 3D");

  wc.lpszClassName = test.m_data;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);

  if (!RegisterClass(&wc))
    return 1;

  DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
  RECT wr = {0, 0, g_app.width, g_app.height};
  AdjustWindowRect(&wr, style, FALSE);

  HWND hwnd = CreateWindow(
                wc.lpszClassName,
                test.m_data,
                style,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                wr.right - wr.left,
                wr.bottom - wr.top,
                NULL,
                NULL,
                hInstance,
                NULL
              );

  if (!hwnd)
    return 1;

  HDC hdc = GetDC(hwnd);
  if (!hdc)
    return 1;

  PIXELFORMATDESCRIPTOR pfd;
  ZeroMemory(&pfd, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 24;
  pfd.iLayerType = PFD_MAIN_PLANE;

  int pf = ChoosePixelFormat(hdc, &pfd);
  if (pf == 0)
    return 1;
  if (!SetPixelFormat(hdc, pf, &pfd))
    return 1;

  HGLRC glrc = wglCreateContext(hdc);
  if (!glrc)
    return 1;
  if (!wglMakeCurrent(hdc, glrc))
    return 1;

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  ShowWindow(hwnd, nShowCmd);
  g_app.camera.captureMouse(hwnd, true);

  QueryPerformanceFrequency(&g_app.freq);
  QueryPerformanceCounter(&g_app.prevTime);

  MSG msg;
  while (g_app.running)
  {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
      {
        g_app.running = false;
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    double dt64 = (double)(now.QuadPart - g_app.prevTime.QuadPart) / (double)g_app.freq.QuadPart;
    g_app.prevTime = now;

    float dt = (float)dt64;
    if (dt > 0.1f)
      dt = 0.1f;

    g_app.camera.update(hwnd, g_app.keys, dt);
    app_render(&g_app);
    SwapBuffers(hdc);
  }

  g_app.camera.captureMouse(hwnd, false);
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(glrc);
  ReleaseDC(hwnd, hdc);

  return 0;
}
