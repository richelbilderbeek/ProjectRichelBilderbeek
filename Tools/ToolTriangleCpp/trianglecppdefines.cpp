#include "trianglecppdefines.h"


#include "trianglecppmesh.h"

int tricpp::vertextype(const double * const vx, const Mesh& m)
{
  return static_cast<int>(vx[m.vertexmarkindex + 1]);
}

void tricpp::Split(const double a, double& ahi, double& alo)
{
  static const double splitter = Global().m_splitter;
  const double c = splitter * a;
  const double abig = c - a;
  ahi = c - abig;
  alo = a - ahi;
}

/*
#define Split(a, ahi, alo) \
  c = (double) (Global().m_splitter * a); \
  abig = (double) (c - a); \
  ahi = c - abig; \
  alo = a - ahi
*/

void tricpp::Two_Diff(const double a, const double b, double& x, double& y)
{
  x = a - b;
  Two_Diff_Tail(a, b, x, y);
}

/*
#define Two_Diff(a, b, x, y) \
  x = (double) (a - b); \
  Two_Diff_Tail(a, b, x, y)
*/

void tricpp::Two_Diff_Tail(const double a, const double b, const double x, double& y)
{
  const double bvirt = a - x;
  const double avirt = x + bvirt;
  const double bround = bvirt - b;
  const double around = a - avirt;
  y = around + bround;
}

/*

#define Two_Diff_Tail(a, b, x, y) \
  bvirt = (double) (a - x); \
  avirt = x + bvirt; \
  bround = bvirt - b; \
  around = a - avirt; \
  y = around + bround

*/

void tricpp::Fast_Two_Sum(const double a, const double b, double& x, double& y)
{
  x = a + b;
  Fast_Two_Sum_Tail(a, b, x, y);
}

/*
#define Fast_Two_Sum(a, b, x, y) \
  x = (double) (a + b); \
  tricpp::Fast_Two_Sum_Tail(a, b, x, y)
*/

void tricpp::Fast_Two_Sum_Tail(const double a, const double b, const double x, double& y)
{
  const double bvirt = x - a;
  y = b - bvirt;
}

/*
#define Fast_Two_Sum_Tail(a, b, x, y) \
  bvirt = x - a; \
  y = b - bvirt
*/

void tricpp::Square(const double a, double& x, double& y)
{
  // Square() can be done more quickly than Two_Product()
  x = a * a;
  Square_Tail(a, x, y);
}

/*
#define Square(a, x, y) \
  x = (double) (a * a); \
  Square_Tail(a, x, y)
*/

void tricpp::Square_Tail(const double a, const double x, double& y)
{
  double ahi = 0.0;
  double alo = 0.0;
  Split(a, ahi, alo);
  const double err1 = x - (ahi * ahi);
  const double err3 = err1 - ((ahi + ahi) * alo);
  y = (alo * alo) - err3;
}

/*
#define Square_Tail(a, x, y) \
  Split(a, ahi, alo); \
  err1 = x - (ahi * ahi); \
  err3 = err1 - ((ahi + ahi) * alo); \
  y = (alo * alo) - err3
*/

void tricpp::Two_One_Diff(const double a1, const double a0, const double b, double& x2, double& x1, double& x0)
{
  double i = 0.0;
  Two_Diff(a0, b , i, x0);
  Two_Sum( a1, i, x2, x1);
}

/*
#define Two_One_Diff(a1, a0, b, x2, x1, x0) \
  Two_Diff(a0, b , _i, x0); \
  Two_Sum( a1, _i, x2, x1)
*/

void tricpp::Two_One_Product(const double a1, const double a0, const double b, double& x3, double& x2, double& x1, double& x0)
{
  double zero = 0.0;
  double i = 0.0;
  double j = 0.0;
  double k = 0.0;
  double bhi = 0.0;
  double blo = 0.0;
  Split(b, bhi, blo);
  Two_Product_Presplit(a0, b, bhi, blo, i, x0);
  Two_Product_Presplit(a1, b, bhi, blo, j, zero);
  Two_Sum(i, zero, k, x1);
  Fast_Two_Sum(j, k, x3, x2);
}

/*
#define Two_One_Product(a1, a0, b, x3, x2, x1, x0) \
  Split(b, bhi, blo); \
  Two_Product_Presplit(a0, b, bhi, blo, _i, x0); \
  Two_Product_Presplit(a1, b, bhi, blo, _j, _0); \
  Two_Sum(_i, _0, _k, x1); \
  Fast_Two_Sum(_j, _k, x3, x2)
*/


void tricpp::Two_One_Sum(const double a1, const double a0, const double b, double& x2, double& x1, double& x0)
{
  double i = 0.0;
  Two_Sum(a0, b , i, x0);
  Two_Sum(a1, i, x2, x1);
}

/*

#define Two_One_Sum(a1, a0, b, x2, x1, x0) \
  Two_Sum(a0, b , _i, x0); \
  Two_Sum(a1, _i, x2, x1)

*/

void tricpp::Two_Product(const double a, const double b, double& x, double& y)
{
  x = a * b;
  Two_Product_Tail(a, b, x, y);
}

/*
#define Two_Product(a, b, x, y) \
  x = (double) (a * b); \
  Two_Product_Tail(a, b, x, y)
*/

void tricpp::Two_Product_Presplit(const double a, const double b, const double bhi, const double blo, double& x, double& y)
{
  // Two_Product_Presplit() is Two_Product() where one of the inputs has
  //   already been split.  Avoids redundant splitting.
  x = a * b;
  double ahi = 0.0;
  double alo = 0.0;
  Split(a, ahi, alo);
  const double err1 = x - (ahi * bhi);
  const double err2 = err1 - (alo * bhi);
  const double err3 = err2 - (ahi * blo);
  y = (alo * blo) - err3;
}

/*
#define Two_Product_Presplit(a, b, bhi, blo, x, y) \
  x = (double) (a * b); \
  Split(a, ahi, alo); \
  err1 = x - (ahi * bhi); \
  err2 = err1 - (alo * bhi); \
  err3 = err2 - (ahi * blo); \
  y = (alo * blo) - err3
*/

void tricpp::Two_Product_Tail(const double a, const double b, const double x, double& y)
{
  double ahi = 0.0;
  double alo = 0.0;
  double bhi = 0.0;
  double blo = 0.0;
  Split(a, ahi, alo);
  Split(b, bhi, blo);
  const double err1 = x - (ahi * bhi);
  const double err2 = err1 - (alo * bhi);
  const double err3 = err2 - (ahi * blo);
  y = (alo * blo) - err3;
}

/*
#define Two_Product_Tail(a, b, x, y) \
  Split(a, ahi, alo); \
  Split(b, bhi, blo); \
  err1 = x - (ahi * bhi); \
  err2 = err1 - (alo * bhi); \
  err3 = err2 - (ahi * blo); \
  y = (alo * blo) - err3
*/

void tricpp::Two_Sum(const double a, const double b, double& x, double& y)
{
  x = a + b;
  Two_Sum_Tail(a, b, x, y);
}

/*
#define Two_Sum(a, b, x, y) \
  x = (double) (a + b); \
  Two_Sum_Tail(a, b, x, y)
*/

void tricpp::Two_Sum_Tail(const double a, const double b, const double x, double& y)
{
  const double bvirt = static_cast<double>(x - a);
  const double avirt = x - bvirt;
  const double bround = b - bvirt;
  const double around = a - avirt;
  y = around + bround;
}

/*
#define Two_Sum_Tail(a, b, x, y) \
  bvirt = (double) (x - a); \
  avirt = x - bvirt; \
  bround = b - bvirt; \
  around = a - avirt; \
  y = around + bround
*/

void tricpp::Two_Two_Diff(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0)
{
  double zero = 0.0;
  double j = 0.0;
  Two_One_Diff(a1, a0, b0,  j, zero, x0);
  Two_One_Diff( j, zero, b1, x3, x2, x1);
}

/*
#define Two_Two_Diff(a1, a0, b1, b0, x3, x2, x1, x0) \
  Two_One_Diff(a1, a0, b0, _j, _0, x0); \
  Two_One_Diff(_j, _0, b1, x3, x2, x1)
*/

void tricpp::Two_Two_Sum(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0)
{
  double zero = 0.0;
  double j = 0.0;
  Two_One_Sum(a1, a0, b0,  j, zero, x0);
  Two_One_Sum( j, zero, b1, x3, x2, x1);
}

/*
#define Two_Two_Sum(a1, a0, b1, b0, x3, x2, x1, x0) \
  Two_One_Sum(a1, a0, b0, _j, _0, x0); \
  Two_One_Sum(_j, _0, b1, x3, x2, x1)
*/
