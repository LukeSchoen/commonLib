#include "clRenderObject.h"
#include "gl_api.h"

void clRenderObject::init(clMesh *mesh, clV3 position)
{
  this->mesh = mesh;
  this->position = position;
}

void clRenderObject::draw()
{
  if (!this->mesh)
    return;

  glPushMatrix();
  glTranslatef(this->position.x, this->position.y, this->position.z);
  this->mesh->draw();
  glPopMatrix();
}
