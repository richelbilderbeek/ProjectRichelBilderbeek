#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "modelfunctionparser.h"

#include <cassert>
#include <stdexcept>

#include <boost/math/constants/constants.hpp>

//Warp's function parser
#include "fparser.hh"

#include "ribi_random.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::ModelFunctionParser::ModelFunctionParser(
  const std::string& my_function,
  const std::string& variable_name)
  : m_parser{new FunctionParser}
{
  #ifndef NDEBUG
  Test();
  #endif
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
  return (*max) * Random().GetFraction();
}

#ifndef NDEBUG
void ribi::ModelFunctionParser::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  {
    const ModelFunctionParser p("x * x * sin(x) * rand(x)","x");
    p.Evaluate(0.0);
  }
  {
    const ModelFunctionParser p("0.0","x");
    assert(std::abs(p.Evaluate(0.0) - 0.0) < 0.0001);
  }

  assert(!"Refactor");
}
#endif
