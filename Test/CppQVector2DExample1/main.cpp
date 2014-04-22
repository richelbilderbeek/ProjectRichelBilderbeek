#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include "QVector2D"
#pragma GCC diagnostic pop

int main()
{
  {
    //Basics
    QVector2D p;
    p.setX(1.0);
    p.setY(2.0);
    assert(p.x() == 1.0);
    assert(p.y() == 2.0);
  }
  {
    //distanceToPoint
    const QVector2D a(3.0,4.0);
    assert(qFuzzyCompare(static_cast<float>(5.0),a.distanceToPoint(QVector2D(0.0,0.0))));
  }
  {
    //dotProduct
    //From https://en.wikipedia.org/wiki/Dotproduct
    //'In particular, if A and B are orthogonal, then [...] A dot b = 0'
    const QVector2D a(1.0,0.0);
    const QVector2D b(0.0,1.0);
    const double p { QVector2D::dotProduct(a,b) };
    const double q { QVector2D::dotProduct(b,a) };
    const double expected { 0.0 };
    assert(qFuzzyCompare(p,expected));
    assert(qFuzzyCompare(q,expected));
  }

}
