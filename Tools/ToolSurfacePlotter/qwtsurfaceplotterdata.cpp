#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwtsurfaceplotterdata.h"

#include <cassert>

#include <boost/make_shared.hpp>

#include "fparser.hh"

#pragma GCC diagnostic pop


ribi::QwtSurfacePlotterData::QwtSurfacePlotterData(
  const boost::shared_ptr<FunctionParser>& function_parser,
  //const std::string& function_str,
  const double minx, const double maxx,
  const double miny, const double maxy,
  const double minz, const double maxz
  )
  : //m_function_parser(boost::make_shared<FunctionParser>())
    m_function_parser(function_parser)
{
  assert(m_function_parser);
  //m_function_parser->Parse(function_str,"x,y");
  //if (m_function_parser->GetParseErrorType() != FunctionParser::FP_NO_ERROR)
  //{
  //  std::stringstream s;
  //  s << "ribi::MyData::MyData: Cannot parse " << function_str;
  //  throw std::logic_error(s.str().c_str());
  //}

  setInterval(Qt::XAxis, QwtInterval(minx,maxx));
  setInterval(Qt::YAxis, QwtInterval(miny,maxy));
  setInterval(Qt::ZAxis, QwtInterval(minz,maxz));
}

double ribi::QwtSurfacePlotterData::value(const double x, const double y) const noexcept
{

  const double xs[2] = { x,y };
  const double z = m_function_parser->Eval(xs);
  if (!m_function_parser->EvalError())
  {
    return z;
  }
  else
  {
    assert(!"Should not get here");
    return 0.0;
  }

  /*
  const double c = 0.842;

  const double v1 = x * x + ( y - c ) * ( y + c );
  const double v2 = x * ( y + c ) + x * ( y + c );

  return 1.0 / ( v1 * v1 + v2 * v2 );
  */
}
