#ifndef TRIANGLECPPDEFINES_H
#define TRIANGLECPPDEFINES_H

#ifdef TRIANGLECPP_USE_DEFINES

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppfwd.h"
#include "trianglecppglobals.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {


//Fast_Two_Sum(a,b,x,y) : x = a + b, y = 0.0;
//void Fast_Two_Sum(const double a, const double b, double& x, double& y);

//y = b - x + a
//void Fast_Two_Sum_Tail(const double a, const double b, const double x, double& y);
void Fast_Two_Sum_Tail_Smartass(const double a, const double b, const double x, double& y);

//ahi = a
//void Split(const double a, double& ahi, double& alo);
void Split_Smartass(const double a, double& ahi, double& alo);

//x = a * a, y = 0.0
//void Square(const double a, double& x, double& y);

//y = - x + (a * a);
//void Square_Tail(const double a, const double x, double& y);
void Square_Tail_Smartass(const double a, const double x, double& y);

//x = a - b, y = 0.0
//void Two_Diff(const double a, const double b, double& x, double& y);
void Two_Diff_Smartass(const double a, const double b, double& x, double& y);

//Two_Diff_Tail(a,b,x,y): y = -x + a - b;
//void Two_Diff_Tail(const double a, const double b, const double x, double& y);
void Two_Diff_Tail_Smartass(const double a, const double b, const double x, double& y);

//Two_One_Diff(a1,a0,b,x2,x1,x0): x2 = a1 + a0 - b, x1 = 0.0, x0 = 0.0
//void Two_One_Diff(const double a1, const double a0, const double b, double& x2, double& x1, double& x0);
void Two_One_Diff_Smartass(const double a1, const double a0, const double b, double& x2, double& x1, double& x0);

//Two_One_Product(a1,a0,b,x3,x2,x1,x0): x3 = (a1 + a0) * b
//void Two_One_Product(const double a1, const double a0, const double b, double& x3, double& x2, double& x1, double& x0);
void Two_One_Product_Smartass(const double a1, const double a0, const double b, double& x3, double& x2, double& x1, double& x0);

//Two_One_Sum(a1,a0,b,x2,x1,x0): x2 = a1 + a0 + n, x1 = 0.0, x0 = 0.0
//void Two_One_Sum(const double a1, const double a0, const double b, double& x2, double& x1, double& x0);

//Two_Product(a,b,x,y): x = a*b, y = 0.0;
//void Two_Product(const double a, const double b, double& x, double& y);

//Two_Product_Presplit(a,b,bhi,blo,x,y): x = a*b, y = 0.0
//void Two_Product_Presplit(const double a, const double b, const double bhi, const double blo, double& x, double& y);

void Two_Product_Presplit_Smartass(const double a, const double b, const double bhi, const double blo, double& x, double& y);
//void Two_Product_Tail(const double a, const double b, const double x, double& y);
void Two_Product_Tail_Smartass(const double a, const double b, const double x, double& y);

//x = a + b, y = 0.0;
//void Two_Sum(const double a, const double b, double& x, double& y);
void Two_Sum_Smartass(const double a, const double b, double& x, double& y);

//y = b - x + a;
//void Two_Sum_Tail(const double a, const double b, const double x, double& y);
void Two_Sum_Tail_Smartass(const double a, const double b, const double x, double& y);

//Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
//void Two_Two_Diff(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0);

//x3 = a1 + a0 + b1 + b0;
//x3 = j + zero + b1;
//x2 = 0.0;
//x1 = 0.0;
//x0 = 0.0;
//Two_Two_Sum(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 + b1 + b0, x2=0.0, x1=0.0, x0=0.0
//void Two_Two_Sum(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPP_USE_DEFINES

#endif // TRIANGLECPPDEFINES_H
