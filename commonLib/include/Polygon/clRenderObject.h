#ifndef clRenderObject_h
#define clRenderObject_h

#include "clMesh.h"

class clRenderObject
{
public:
  clMesh *mesh;
  clV3 position;

  void init(clMesh *mesh, clV3 position);
  void draw();
};

#endif
