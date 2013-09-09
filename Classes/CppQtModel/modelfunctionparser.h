#ifndef MODELFUNCTIONPARSER_H
#define MODELFUNCTIONPARSER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct FunctionParser;

namespace ribi {

///Uses Warp's function parser and adds a random function
struct ModelFunctionParser
{
  ModelFunctionParser(const ModelFunctionParser&e) = delete;
  ModelFunctionParser& operator=(const ModelFunctionParser&e) = delete;

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
