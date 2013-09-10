#ifndef NOISEFUNCTIONPARSER_H
#define NOISEFUNCTIONPARSER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#pragma GCC diagnostic pop

struct FunctionParser;

namespace ribi {

///Uses Warp's function parser and adds a random function
struct NoiseFunctionParser : public boost::noncopyable
{
  ///For example:
  ///my_function = 'x * x * sin(x) * rand(x)'
  ///variable_name = 'x'
  NoiseFunctionParser(const std::string& my_function, const std::string& variable_name);

  ///Calculate the y for 'y = f(x)'
  double Evaluate(const double x) const;

  private:
  const boost::shared_ptr<FunctionParser> m_parser;

  static double MyRand(const double * const max);

};

} //~namespace ribi

#endif // NOISEFUNCTIONPARSER_H
