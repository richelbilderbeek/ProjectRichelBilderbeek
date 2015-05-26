#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "noisefunctionparser.h"

#include <cassert>
#include <stdexcept>

//Warp's function parser
#include "fparser.hh"
#include "ribi_random.h"

#pragma GCC diagnostic pop

ribi::NoiseFunctionParser::NoiseFunctionParser(
  const std::string& my_function,
  const std::string& variable_name)
  : m_parser(new FunctionParser)
{
  assert(m_parser);
  m_parser->AddFunction("rand",MyRand,1);
  m_parser->Parse(my_function,variable_name);

  if (m_parser->GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    const std::string error
      = "InputFunctionParser cannot parse '"
      + my_function
      + "' with variable '"
      + variable_name
      + "'";
    throw std::runtime_error(error.c_str());
  }
}

double ribi::NoiseFunctionParser::Evaluate(const double x) const
{
  const double xs[1] = { x };
  const double y = m_parser->Eval(xs);
  return y;
}

double ribi::NoiseFunctionParser::MyRand(const double * const max)
{
  assert(max);
  return (*max) * Random().GetFraction();
}
