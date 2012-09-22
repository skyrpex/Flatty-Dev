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

qreal Math::normalizedAngle(qreal angle)
{
  angle = modulo(angle, 360.0);
  if(angle < 0.0)
    return angle + 360.0;

  return angle;
}

qreal Math::fullAngle(qreal angle)
{
  return normalizedAngle(angle);
}

qreal Math::halfAngle(qreal angle)
{
  angle = modulo(angle, 360.0);
  if(angle > 180.0)
    return modulo(angle, 180.0) - 180.0;

  return angle;
}
