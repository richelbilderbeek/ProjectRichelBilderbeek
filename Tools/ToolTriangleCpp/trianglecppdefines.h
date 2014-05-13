#ifndef TRIANGLECPPDEFINES_H
#define TRIANGLECPPDEFINES_H

#include "trianglecppfwd.h"
#include "trianglecppglobals.h"

namespace tricpp {

int vertextype(const double * const vx, const Mesh& m);
void Fast_Two_Sum_Tail(const double a, const double b, const double x, double& y);
void Fast_Two_Sum(const double a, const double b, double& x, double& y);
void Two_Sum_Tail(const double a, const double b, const double x, double& y);
void Two_Sum(const double a, const double b, double& x, double& y);
void Two_Diff_Tail(const double a, const double b, const double x, double& y);
void Two_Diff(const double a, const double b, double& x, double& y);
void Split(const double a, double& ahi, double& alo);
void Two_Product_Tail(const double a, const double b, const double x, double& y);
void Two_Product(const double a, const double b, double& x, double& y);
void Two_Product_Presplit(const double a, const double b, const double bhi, const double blo, double& x, double& y);
void Square_Tail(const double a, const double x, double& y);
void Square(const double a, double& x, double& y);
void Two_One_Sum(const double a1, const double a0, const double b, double& x2, double& x1, double& x0);
void Two_One_Diff(const double a1, const double a0, const double b, double& x2, double& x1, double& x0);
void Two_Two_Sum(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0);
void Two_Two_Diff(const double a1, const double a0, const double b1, const double b0, double& x3, double& x2, double& x1, double& x0);
void Two_One_Product(const double a1, const double a0, const double b, double& x3, double& x2, double& x1, double& x0);

} //~namespace tricpp

#endif // TRIANGLECPPDEFINES_H
