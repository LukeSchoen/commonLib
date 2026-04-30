#ifndef clV3_h
#define clV3_h

class clV3
{
public:
  float x, y, z;

  clV3();
  void set(float x, float y, float z);
  class clV3 add(class clV3 b);
  class clV3 sub(class clV3 b);
  class clV3 scale(float s);
  float length();
  class clV3 normalize();
  class clV3 cross(class clV3 b);
};

#endif
