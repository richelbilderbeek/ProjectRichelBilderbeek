#include "trianglecppdefines.h"


#include "trianglecppmesh.h"

/*
void ribi::tricpp::Split(const double a, double& ahi, double& alo)
{
  static const double splitter = Global().m_splitter;
  const double c = (splitter * a);
  //const double abig = c - a;
  //const double abig = (splitter * a) - a;
  //ahi = c - ((splitter * a) - a);
  //ahi = (splitter * a) - ((splitter * a) - a);
  //ahi = (splitter * a) - (splitter * a) + a;
  ahi = a;
  //ahi = c - abig;
  //alo = a - (c - ((splitter * a) - a));
  //alo = a - ((splitter * a) - ((splitter * a) - a));
  //alo = a - (splitter * a) + (splitter * a) - a;
  alo = 0.0;
  //alo = a - ahi;
  {
    double temp_ahi = 0.0;
    double temp_alo = 0.0;
    Split_Smartass(a,temp_ahi,temp_alo);
    assert(temp_ahi = ahi);
    assert(temp_alo = alo);
  }
}
*/

void ribi::tricpp::Split_Smartass(const double a, double& ahi, double& alo)
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

/*
void ribi::tricpp::Two_Diff(const double a, const double b, double& x, double& y)
{
  x =      a - b;
  //y = -x + a - b;
  //y = -(a - b) + a - b;
  //y = -a + b + a - b;
  y = 0.0;
  //Two_Diff_Tail(a, b, x, y);
}
*/

void ribi::tricpp::Two_Diff_Smartass(const double a, const double b, double& x, double& y)
{
  x = a - b;
  Two_Diff_Tail_Smartass(a, b, x, y);
}

/*
#define Two_Diff(a, b, x, y) \
  x = (double) (a - b); \
  Two_Diff_Tail(a, b, x, y)
*/

/*
void ribi::tricpp::Two_Diff_Tail(const double a, const double b, const double x, double& y)
{
  //const double bvirt = (a - x);
  //const double avirt = (x + (a - x));
  //const double bround = (a - x) - b;
  //const double around = (a - (x + (a - x)));
  //y = (a - (x + (a - x))) + (a - x) - b;
  //y = (a - (x + a - x)) + a - x - b;
  //y = (a - x - a + x) + a - x - b;
  y = -x + a - b;
}
*/

void ribi::tricpp::Two_Diff_Tail_Smartass(const double a, const double b, const double x, double& y)
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

/*
void ribi::tricpp::Fast_Two_Sum(const double a, const double b, double& x, double& y)
{
  x = a + b;
  //y = -x + a + b;
  y = 0.0;
  //y = b - x + a;
  //Fast_Two_Sum_Tail(a, b, x, y);
}
*/
/*
#define Fast_Two_Sum(a, b, x, y) \
  x = (double) (a + b); \
  ribi::tricpp::Fast_Two_Sum_Tail(a, b, x, y)
*/

/*
void ribi::tricpp::Fast_Two_Sum_Tail(const double a, const double b, const double x, double& y)
{
  //const double bvirt = x - a;
  y = b - x + a;
}
*/
void ribi::tricpp::Fast_Two_Sum_Tail_Smartass(const double a, const double b, const double x, double& y)
{
  const double bvirt = x - a;
  y = b - bvirt;
}

/*
#define Fast_Two_Sum_Tail(a, b, x, y) \
  bvirt = x - a; \
  y = b - bvirt
*/

/*
void ribi::tricpp::Square(const double a, double& x, double& y)
{
  const double x_temp = x;
  const double y_temp = y;
  //y = - x + (a * a);
  //x = a * a;
  //y = - (a * a) + (a * a);
  //y = - x + (a * a);
  //Square_Tail(a, x, y);
  y = 0.0;
  // Square() can be done more quickly than Two_Product()
  x = a * a;


  Square_Tail_Smartass(a, x_temp, y_temp);
  assert(x == x_temp);
  assert(y == y_temp);
}
*/

/*
#define Square(a, x, y) \
  x = (double) (a * a); \
  Square_Tail(a, x, y)
*/

/*
void ribi::tricpp::Square_Tail(const double a, const double x, double& y)
{
  //double ahi = 0.0;
  //double alo = 0.0;
  //Split(a, ahi, alo);
  //assert(ahi == a); assert(alo == 0.0);
  //const double err1 = x - (a * a);
  //const double err1 = x - (ahi * ahi);

  //const double err3 = err1;
  //const double err3 = err1 - ((a + a) * 0.0);
  //const double err3 = err1 - ((ahi + ahi) * alo);
  //y = (alo * alo) - err3;
  //y = - err3;
  //y = - err1;
  y = - x + (a * a);
  {
    double y_temp = 0.0;
    Square_Tail_Smartass(a,x,y_temp);
    assert(y == y_temp);
  }
}
*/

void ribi::tricpp::Square_Tail_Smartass(const double a, const double x, double& y)
{
  double ahi = 0.0;
  double alo = 0.0;
  Split_Smartass(a, ahi, alo);
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

/*
void ribi::tricpp::Two_One_Diff(const double a1, const double a0, const double b, double& x2, double& x1, double& x0)
{
  //double i = 0.0;
  //x = a - b, y = 0.0
  //Two_Diff(a0, b , i, x0);
  //const double i = a0 - b;
  x0 = 0.0;
  x2 = a1 + a0 - b;
  //x2 = a1 + i;
  x1 = 0.0;
  //x = a + b, y = 0.0;
  //Two_Sum( a1, i, x2, x1);
}
*/
void ribi::tricpp::Two_One_Diff_Smartass(const double a1, const double a0, const double b, double& x2, double& x1, double& x0)
{
  double i = 0.0;
  Two_Diff_Smartass(a0, b , i, x0);

  x2 = a1 + i;
  x1 = 0.0;
  //x = a + b, y = 0.0;
  //Two_Sum( a1, i, x2, x1);
}

/*
#define Two_One_Diff(a1, a0, b, x2, x1, x0) \
  Two_Diff(a0, b , _i, x0); \
  Two_Sum( a1, _i, x2, x1)
*/

/*
void ribi::tricpp::Two_One_Product(const double a1, const double a0, const double b, double& x3, double& x2, double& x1, double& x0)
{
  //double zero = 0.0;
  //double i = 0.0;
  //double j = 0.0;
  //double k = 0.0;
  //double bhi = 0.0;
  //double blo = 0.0;
  //bhi = b;
  //blo = 0.0;
  //Split(b, bhi, blo);

  //double i = a0 * b;
  //Two_Product_Presplit(a,b,bhi,blo,x,y): x = a*b, y = 0.0
  //Two_Product_Presplit(a0, b, bhi, blo, i, x0);

  //double j = a1 * b;
  //Two_Product_Presplit(a,b,bhi,blo,x,y): x = a*b, y = 0.0
  //Two_Product_Presplit(a1, b, bhi, blo, j, zero);

  //double k = a0 * b;
  //double k = i + zero;

  x1 = 0.0;
  //x = a + b, y = 0.0;
  //Two_Sum(i, zero, k, x1);

  x3 = (a1 + a0) * b;
  //x3 = (a1 * b) + (a0 * b);
  //x3 = j + k;
  //Fast_Two_Sum(a,b,x,y) : x = a + b, y = 0.0;
  //Fast_Two_Sum(j, k, x3, x2);
}
*/
void ribi::tricpp::Two_One_Product_Smartass(const double a1, const double a0, const double b, double& x3, double& x2, double& x1, double& x0)
{
  double zero = 0.0;
  double i = 0.0;
  double j = 0.0;
  double k = 0.0;
  double bhi = 0.0;
  double blo = 0.0;
  Split_Smartass(b, bhi, blo);

  i = a0 * b;
  //Two_Product_Presplit(a,b,bhi,blo,x,y): x = a*b, y = 0.0
  //Two_Product_Presplit(a0, b, bhi, blo, i, x0);

  j = a1 * b;
  //Two_Product_Presplit(a,b,bhi,blo,x,y): x = a*b, y = 0.0
  //Two_Product_Presplit(a1, b, bhi, blo, j, zero);

  k = i + zero;
  x1 = 0.0;
  //x = a + b, y = 0.0;
  //Two_Sum(i, zero, k, x1);

  Fast_Two_Sum_Smartass(j, k, x3, x2);
}

/*
#define Two_One_Product(a1, a0, b, x3, x2, x1, x0) \
  Split(b, bhi, blo); \
  Two_Product_Presplit(a0, b, bhi, blo, _i, x0); \
  Two_Product_Presplit(a1, b, bhi, blo, _j, _0); \
  Two_Sum(_i, _0, _k, x1); \
  Fast_Two_Sum(_j, _k, x3, x2)
*/

/*
void ribi::tricpp::Two_One_Sum(const double a1, const double a0, const double b, double& x2, double& x1, double& x0)
{
  //const double i = a0 + b;
  x0 = 0.0;
  //x = a + b, y = 0.0;
  //Two_Sum(a0, b , i, x0);

  x2 = a1 + a0 + b;
  //x2 = a1 + i;
  x1 = 0.0;
  //x = a + b, y = 0.0;
  //Two_Sum(a1, i, x2, x1);
}
*/
void ribi::tricpp::Two_One_Sum_Smartass(const double a1, const double a0, const double b, double& x2, double& x1, double& x0)
{
  double i = 0.0;
  Two_Sum_Smartass(a0, b , i, x0);
  Two_Sum_Smartass(a1, i, x2, x1);
}

/*

#define Two_One_Sum(a1, a0, b, x2, x1, x0) \
  Two_Sum(a0, b , _i, x0); \
  Two_Sum(a1, _i, x2, x1)

*/
/*
void ribi::tricpp::Two_Product(const double a, const double b, double& x, double& y)
{
  x = a * b;
  y = 0.0;
  //Two_Product_Tail(a, b, x, y);
}
*/
/*
#define Two_Product(a, b, x, y) \
  x = (double) (a * b); \
  Two_Product_Tail(a, b, x, y)
*/

/*
void ribi::tricpp::Two_Product_Presplit(const double a, const double b, const double bhi, const double blo, double& x, double& y)
{
  x = a * b;
  y = 0.0;
}
*/

void ribi::tricpp::Two_Product_Presplit_Smartass(const double a, const double b, const double bhi, const double blo, double& x, double& y)
{
  // Two_Product_Presplit() is Two_Product() where one of the inputs has
  //   already been split.  Avoids redundant splitting.
  x = a * b;
  double ahi = 0.0;
  double alo = 0.0;
  Split_Smartass(a, ahi, alo);
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

/*
void ribi::tricpp::Two_Product_Tail(const double a, const double b, const double x, double& y)
{
  y = 0.0 - x + (a * b);
}
*/

void ribi::tricpp::Two_Product_Tail_Smartass(const double a, const double b, const double x, double& y)
{
  double ahi = 0.0;
  double alo = 0.0;
  double bhi = 0.0;
  double blo = 0.0;
  Split_Smartass(a, ahi, alo);
  Split_Smartass(b, bhi, blo);
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

/*
void ribi::tricpp::Two_Sum(const double a, const double b, double& x, double& y)
{
  x = a + b;
  y = 0.0;
  //y = -a - b + b + a;
  //y = -x + b + a;
  //y = b - x + a;
  //Two_Sum_Tail(a, b, x, y);
}
*/

void ribi::tricpp::Two_Sum_Smartass(const double a, const double b, double& x, double& y)
{
  x = a + b;
  Two_Sum_Tail_Smartass(a, b, x, y);
}

/*
#define Two_Sum(a, b, x, y) \
  x = (double) (a + b); \
  Two_Sum_Tail(a, b, x, y)
*/

/*
void ribi::tricpp::Two_Sum_Tail(const double a, const double b, const double x, double& y)
{
  //y = (a - (x - (x - a))) + (b - (x - a));
  //y =  a - (x - (x - a))  +  b - (x - a);
  //y =  a - (x -  x + a )  +  b -  x + a;
  //y =  a -  x +  x - a    +  b -  x + a;
  y = b - x + a;
  {
    double tempy_y = 0.0;
    Two_Sum_Tail_Smartass(a,b,x,tempy_y);
    assert(y == tempy_y);
  }
}
*/

void ribi::tricpp::Two_Sum_Tail_Smartass(const double a, const double b, const double x, double& y)
{
  const double bvirt = x - a;
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

/*
void ribi::tricpp::Two_Two_Diff(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0)
{
  //double zero = 0.0;
  //double j = 0.0;

  const double j = a1 + a0 - b0;
  const double zero = 0.0;
  x0 = 0.0;
  //Two_One_Diff(a1,a0,b,x2,x1,x0): x2 = a1 + a0 - b, x1 = 0.0, x0 = 0.0
  //Two_One_Diff(a1, a0, b0,  j, zero, x0);

  x3 = a1 + a0 - b0 - b1;
  //x3 = j - b1;
  //x3 = j + zero - b1;
  x2 = 0.0;
  x1 = 0.0;
  //Two_One_Diff(a1,a0,b,x2,x1,x0): x2 = a1 + a0 - b, x1 = 0.0, x0 = 0.0
  //Two_One_Diff( j, zero, b1, x3, x2, x1);
}
*/
/*
#define Two_Two_Diff(a1, a0, b1, b0, x3, x2, x1, x0) \
  Two_One_Diff(a1, a0, b0, _j, _0, x0); \
  Two_One_Diff(_j, _0, b1, x3, x2, x1)
*/
/*
void ribi::tricpp::Two_Two_Sum(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0)
{
  double zero = 0.0;
  double j = 0.0;

  //j = a1 + a0 + b0; zero = 0.0; x0 = 0.0;
  //Two_One_Sum(a1,a0,b,x2,x1,x0): x2 = a1 + a0 + b0n, x1 = 0.0, x0 = 0.0
  //Two_One_Sum(a1, a0, b0,  j, zero, x0);

  //x3 = a1 + a0 + b1 + b0;
  //x3 = j + zero + b1;
  x2 = 0.0;
  x1 = 0.0;
  //Two_One_Sum(a1,a0,b,x2,x1,x0): x2 = a1 + a0 + b0, x1 = 0.0, x0 = 0.0
  //Two_One_Sum( j, zero, b1, x3, x2, x1);
}
*/
/*
#define Two_Two_Sum(a1, a0, b1, b0, x3, x2, x1, x0) \
  Two_One_Sum(a1, a0, b0, _j, _0, x0); \
  Two_One_Sum(_j, _0, b1, x3, x2, x1)
*/
