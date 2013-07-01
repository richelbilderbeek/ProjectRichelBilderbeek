#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "modelfunctionparser.h"

#include <cassert>
#include <stdexcept>

//Warp's function parser
#include "fparser.hh"

ModelFunctionParser::ModelFunctionParser(
  const std::string& my_function,
  const std::string& variable_name)
  : m_parser(new FunctionParser)
{
  assert(m_parser);
  m_parser->AddConstant("pi",M_PI);
  m_parser->AddConstant("tau",2.0*M_PI);
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

double ModelFunctionParser::Evaluate(const double x) const
{
  const double xs[1] = { x };
  const double y = m_parser->Eval(xs);
  return y;
}

double ModelFunctionParser::MyRand(const double * const max)
{
  assert(max);
  return (*max) * static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
}
