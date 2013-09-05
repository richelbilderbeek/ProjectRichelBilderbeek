#ifndef MODELFUNCTIONPARSER_H
#define MODELFUNCTIONPARSER_H

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

struct FunctionParser;

namespace ribi {

///Uses Warp's function parser and adds a random function
struct ModelFunctionParser : public boost::noncopyable
{
  ///For example:
  ///my_function = 'x * x * sin(x) * rand(x)'
  ///variable_name = 'x'
  explicit ModelFunctionParser(const std::string& my_function, const std::string& variable_name);

  ///Calculate the y for 'y = f(x)'
  double Evaluate(const double x) const;

  private:
  const boost::shared_ptr<FunctionParser> m_parser;

  static double MyRand(const double * const max);

};

} //~namespace ribi

#endif // MODELFUNCTIONPARSER_H
