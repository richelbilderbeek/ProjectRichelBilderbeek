#include <cassert>
#include <iostream>
#include <gmtl/gmtl.h>

int main()
{
  const gmtl::Vec3f a { 1.0, 2.0,  3.0 };
  const gmtl::Vec3f b { 4.0, 8.0, 12.0 };
  gmtl::Vec3f result;

  const float w = 1.0 / 3.0;

  ///Obtain the weighted vector between a and b, closest to a:
  /// a[1] = 2.0
  /// b[1] = 8.0
  /// w    = 1.0 / 3.0                       //weight
  /// d    = b[1] - a[1] = 6.0               //distance between a[1] and b[1]
  /// d_a  = w * d = (1.0 / 3.0) * 6.0 = 2.0 //distance from a[1]
  /// r[1] = a[1] + d_a = 2.0 + 2.0 = 4;     //resulting value
  gmtl::lerp( result, w, a, b );

  const double e = 0.000001;
  assert(result[0] > 2.0 - e && result[0] < 2.0 + e);
  assert(result[1] > 4.0 - e && result[1] < 4.0 + e);
  assert(result[2] > 6.0 - e && result[2] < 6.0 + e);
}

