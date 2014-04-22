#include <boost/numeric/ublas/matrix.hpp>

const boost::numeric::ublas::matrix<double> Inverse(
  const boost::numeric::ublas::matrix<double>& m)
{
  assert(m.size1() == m.size2() && "Can only calculate the inverse of square matrices");
  assert(m.size1() == 2 && m.size2() == 2 && "Only for 2x2 matrices");
  boost::numeric::ublas::matrix<double> n(2,2);
  const double a = m(0,0);
  const double b = m(0,1);
  const double c = m(1,0);
  const double d = m(1,1);
  assert((a * d) - (b * c) != 0.0 && "Determinant must be nonzero");
  const double determinant = 1.0 / ((a * d) - (b * c));
  n(0,0) =  d * determinant;
  n(0,1) = -b * determinant;
  n(1,0) = -c * determinant;
  n(1,1) =  a * determinant;
  return n;
}

const boost::numeric::ublas::matrix<double> CreateMatrix()
{
  boost::numeric::ublas::matrix<double> m(2,2); //y-x-ordered
  m(0,0) = 4.0;
  m(0,1) = 7.0;
  m(1,0) = 2.0;
  m(1,1) = 6.0;
  return m;
}

bool IsAboutEqual(const double x, const double y) { return std::abs(x-y) < 0.00001; }

int main()
{
  //Create an example matrix
  const boost::numeric::ublas::matrix<double> m = CreateMatrix();

  assert(IsAboutEqual(m(0,0),4.0)); assert(IsAboutEqual(m(0,1),7.0));
  assert(IsAboutEqual(m(1,0),2.0)); assert(IsAboutEqual(m(1,1),6.0));

  //Obtain the inverse of the example matrix
  const boost::numeric::ublas::matrix<double> n = Inverse(m);

  assert(IsAboutEqual(n(0,0), 0.6)); assert(IsAboutEqual(n(0,1),-0.7));
  assert(IsAboutEqual(n(1,0),-0.2)); assert(IsAboutEqual(n(1,1), 0.4));

  //Check that the product of a matrix and its inverse yields an identity matrix
  const boost::numeric::ublas::matrix<double> p = boost::numeric::ublas::prod(m,n);

  assert(IsAboutEqual(p(0,0),1.0)); assert(IsAboutEqual(p(0,1),0.0));
  assert(IsAboutEqual(p(1,0),0.0)); assert(IsAboutEqual(p(1,1),1.0));
}
