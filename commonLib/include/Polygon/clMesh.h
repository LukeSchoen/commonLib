#ifndef clMesh_h
#define clMesh_h

#include "clV3.h"

class clMesh
{
public:
  int kind;
  float size;
  int gridHalfExtent;
  clV3 color;

  void initCube(float size, clV3 color);
  void initGrid(int halfExtent, clV3 color);
  void draw();
};

enum
{
  MESH_KIND_CUBE = 1,
  MESH_KIND_GRID = 2
};

#endif
