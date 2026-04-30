#include <math.h>
#include "clV3.h"

clV3::clV3()
{
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

void clV3::set(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

class clV3 clV3::add(class clV3 b)
{
  clV3 out;
  out.set(this->x + b.x, this->y + b.y, this->z + b.z);
  return out;
}

class clV3 clV3::sub(class clV3 b)
{
  clV3 out;
  out.set(this->x - b.x, this->y - b.y, this->z - b.z);
  return out;
}

class clV3 clV3::scale(float s)
{
  clV3 out;
  out.set(this->x *s, this->y *s, this->z *s);
  return out;
}

float clV3::length()
{
  return sqrtf(this->x *this->x + this->y *this->y + this->z *this->z);
}

class clV3 clV3::normalize()
{
  float l = sqrtf(this->x *this->x + this->y *this->y + this->z *this->z);
  if (l <= 0.00001f)
  {
    clV3 out;
    out.set(0.0f, 0.0f, 0.0f);
    return out;
  }
  clV3 out;
  out.set(this->x * (1.0f / l), this->y * (1.0f / l), this->z * (1.0f / l));
  return out;
}

class clV3 clV3::cross(class clV3 b)
{
  clV3 out;
  out.set(
       this->y *b.z - this->z *b.y,
       this->z *b.x - this->x *b.z,
       this->x *b.y - this->y *b.x
     );
  return out;
}
