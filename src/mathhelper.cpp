#include "mathhelper.h"
#include <cmath>

qreal Math::modulo(qreal a, qreal b)
{
  return std::fmod(a, b);
}

qreal Math::angleDifference(qreal a, qreal b)
{
  return modulo(modulo(a - b, 360.0) + 540.0, 360.0) - 180.0;
}
