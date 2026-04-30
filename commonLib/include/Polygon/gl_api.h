#ifndef GL_API_H
#define GL_API_H

#include <windows.h>

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef float GLfloat;

#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DEPTH_TEST 0x0B71
#define GL_CULL_FACE 0x0B44
#define GL_PROJECTION 0x1701
#define GL_MODELVIEW 0x1700
#define GL_QUADS 0x0007
#define GL_LINES 0x0001
#define GL_NO_ERROR 0

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllimport) void __stdcall glBegin(GLenum mode);
__declspec(dllimport) void __stdcall glEnd(void);
__declspec(dllimport) void __stdcall glVertex3f(GLfloat x, GLfloat y, GLfloat z);
__declspec(dllimport) void __stdcall glColor3f(GLfloat r, GLfloat g, GLfloat b);
__declspec(dllimport) void __stdcall glPushMatrix(void);
__declspec(dllimport) void __stdcall glPopMatrix(void);
__declspec(dllimport) void __stdcall glTranslatef(GLfloat x, GLfloat y, GLfloat z);
__declspec(dllimport) void __stdcall glLoadIdentity(void);
__declspec(dllimport) void __stdcall glMultMatrixf(const GLfloat *m);
__declspec(dllimport) void __stdcall glMatrixMode(GLenum mode);
__declspec(dllimport) void __stdcall glFrustum(double left, double right, double bottom, double top, double zNear, double zFar);
__declspec(dllimport) void __stdcall glViewport(int x, int y, int width, int height);
__declspec(dllimport) void __stdcall glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
__declspec(dllimport) void __stdcall glClear(GLbitfield mask);
__declspec(dllimport) void __stdcall glEnable(GLenum cap);
__declspec(dllimport) void __stdcall glDisable(GLenum cap);
__declspec(dllimport) unsigned int __stdcall glGetError(void);

#ifdef __cplusplus
}
#endif

#endif
