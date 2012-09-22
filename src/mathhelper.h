#ifndef CLASS_MATH_H
#define CLASS_MATH_H

#include <QtGlobal>

class Math
{
public:
  static qreal modulo(qreal a, qreal b);
  static qreal angleDifference(qreal a, qreal b);
  static qreal normalizedAngle(qreal angle);
  static qreal fullAngle(qreal angle);
  static qreal halfAngle(qreal angle);
  template<class T>
  static inline T catmullRomInterpolation(const T &a, const T &b, const T &c, const T &d,
                                          qreal ta, qreal tb, qreal tc, qreal td, qreal u)
  {
    qreal u2 = u*u;
    qreal u3 = u2*u;
    qreal u23 = u2*3.0;
    qreal u32 = u3*2.0;

    T daux = (c-b)*(0.5/(tc-tb));
    T db = (b-a)*(0.5/(tb-ta)) + daux;
    T dc = daux + (d-c)*(0.5/(td-tc));
    return b*(u32 - u23 + 1.0) + c*(u23 - u32) + db*(u3 - 2.0*u2 + u) + dc*(u3-u2);
  }
};

#endif // CLASS_MATH_H
