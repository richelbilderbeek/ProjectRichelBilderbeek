#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "modelfunctionparser.h"

#include <cassert>
#include <stdexcept>

#include <boost/math/constants/constants.hpp>

//Warp's function parser
#include "fparser.hh"
#pragma GCC diagnostic pop

ribi::ModelFunctionParser::ModelFunctionParser(
  const std::string& my_function,
  const std::string& variable_name)
  : m_parser{new FunctionParser}
{
  assert(m_parser);

  const double pi = boost::math::constants::pi<double>();
  m_parser->AddConstant("pi",pi);
  m_parser->AddConstant("tau",2.0*pi);
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

double ribi::ModelFunctionParser::Evaluate(const double x) const
{
  const double xs[1] = { x };
  const double y = m_parser->Eval(xs);
  return y;
}

double ribi::ModelFunctionParser::MyRand(const double * const max) noexcept
{
  assert(max);
  return (*max) * static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
}
