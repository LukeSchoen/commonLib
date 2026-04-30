#include "clMesh.h"
#include "gl_api.h"

static void draw_cube(float size)
{
  float h = size * 0.5f;

  glBegin(GL_QUADS);
  glVertex3f(-h, -h, +h); glVertex3f(+h, -h, +h); glVertex3f(+h, +h, +h); glVertex3f(-h, +h, +h);
  glVertex3f(-h, -h, -h); glVertex3f(-h, +h, -h); glVertex3f(+h, +h, -h); glVertex3f(+h, -h, -h);
  glVertex3f(-h, +h, -h); glVertex3f(-h, +h, +h); glVertex3f(+h, +h, +h); glVertex3f(+h, +h, -h);
  glVertex3f(-h, -h, -h); glVertex3f(+h, -h, -h); glVertex3f(+h, -h, +h); glVertex3f(-h, -h, +h);
  glVertex3f(+h, -h, -h); glVertex3f(+h, +h, -h); glVertex3f(+h, +h, +h); glVertex3f(+h, -h, +h);
  glVertex3f(-h, -h, -h); glVertex3f(-h, -h, +h); glVertex3f(-h, +h, +h); glVertex3f(-h, +h, -h);
  glEnd();
}

static void draw_grid(int halfExtent)
{
  glBegin(GL_LINES);
  for (int i = -halfExtent; i <= halfExtent; ++i)
  {
    glVertex3f((float)i, 0.0f, (float) - halfExtent);
    glVertex3f((float)i, 0.0f, (float)halfExtent);
    glVertex3f((float) - halfExtent, 0.0f, (float)i);
    glVertex3f((float)halfExtent, 0.0f, (float)i);
  }
  glEnd();
}

void clMesh::initCube(float size, clV3 color)
{
  this->kind = MESH_KIND_CUBE;
  this->size = size;
  this->gridHalfExtent = 0;
  this->color = color;
}

void clMesh::initGrid(int halfExtent, clV3 color)
{
  this->kind = MESH_KIND_GRID;
  this->size = 0.0f;
  this->gridHalfExtent = halfExtent;
  this->color = color;
}

void clMesh::draw()
{
  glColor3f(this->color.x, this->color.y, this->color.z);

  if (this->kind == MESH_KIND_CUBE)
  {
    draw_cube(this->size);
    return;
  }

  if (this->kind == MESH_KIND_GRID)
    draw_grid(this->gridHalfExtent);
}
