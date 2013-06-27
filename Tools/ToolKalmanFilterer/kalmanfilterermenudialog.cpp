#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfilterermenudialog.h"

#include "standardkalmanfilter.h"
#include "steadystatekalmanfilter.h"
#include "standardkalmanfilterparameters.h"
#include "steadystatekalmanfilterparameters.h"
#include "matrix.h"
#include "gapsfilledwhitenoisesystem.h"
#include "trace.h"
#include "laggedwhitenoisesystem.h"
#include "standardwhitenoisesystem.h"
#include "fixedlagsmootherkalmanfilter.h"
#include "standardwhitenoisesystemparameters.h"

const About KalmanFiltererMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "KalmanFilterer",
    "tool to work with Kalman filters",
    "the 27th of June 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolKalmanFilterer.htm",
    GetVersion(),
    GetVersionHistory());
    a.AddLibrary("FixedLagSmootherKalmanFilter version: " + FixedLagSmootherKalmanFilter::GetVersion());
    a.AddLibrary("GapsFilledWhiteNoiseSystem version: " + GapsFilledWhiteNoiseSystem::GetVersion());
    a.AddLibrary("KalmanFilter version: " + KalmanFilter::GetVersion());
    a.AddLibrary("LaggedWhiteNoiseSystem version: " + LaggedWhiteNoiseSystem::GetVersion());
    a.AddLibrary("Matrix version: " + Matrix::GetVersion());
    a.AddLibrary("StandardKalmanFilter version: " + StandardKalmanFilter::GetVersion());
    a.AddLibrary("StandardKalmanFilterParameters version: " + StandardKalmanFilterParameters::GetVersion());
    a.AddLibrary("StandardWhiteNoiseSystem version: " + StandardWhiteNoiseSystem::GetVersion());
    a.AddLibrary("StandardWhiteNoiseSystemParameters version: " + StandardWhiteNoiseSystemParameters::GetVersion());
    a.AddLibrary("SteadyStateKalmanFilter version: " + SteadyStateKalmanFilter::GetVersion());
    a.AddLibrary("SteadyStateKalmanFilterParameters version: " + SteadyStateKalmanFilterParameters::GetVersion());
    a.AddLibrary("Trace version: " + Trace::GetVersion());
    a.AddLibrary("WhiteNoiseSystem version: " + WhiteNoiseSystem::GetVersion());
  return a;
}

const std::string KalmanFiltererMenuDialog::GetVersion()
{
  return "1.11";
}

const std::vector<std::string> KalmanFiltererMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-04-28: version 1.0: initial version that started from CppKalmanFilterExample13");
  v.push_back("2013-05-01: version 1.1: added plotting, added steady-state Kalman filter");
  v.push_back("2013-05-02: version 1.2: fixed messed-up graphs and calculation displayal");
  v.push_back("2013-05-03: version 1.3: improved parameters GUI and use");
  v.push_back("2013-05-06: version 1.4: prepared architecture for expansion");
  v.push_back("2013-05-16: version 1.5: use of model/view architecture, preparations for adding fixed-lag-smoother Kalman filter");
  v.push_back("2013-05-28: version 1.6: added loading (from DokuWiki) and saving (to DokuWiki and HTML) of parameters");
  v.push_back("2013-05-28: version 1.7: added possibility to save graphs to file");
  v.push_back("2013-06-13: version 1.8: fixed bug in parameter tables, allow to view data as a table");
  v.push_back("2013-06-14: version 1.9: allow to copy data from table");
  v.push_back("2013-06-17: version 1.10: removed useless examples");
  v.push_back("2013-06-27: version 1.11: added gaps-filled white noise system");
  //Future ideas:
  //- Add an explanation to the examples, e.g. in the form of an HTML page. This can be done
  //  by adding the DokuWiki's <html></html> tags, with an HTML comment inside to find the explanation:
  //  <html><!-- <explanation> --></html>
  //  This example is about a flying cannonball
  //  <html><!-- </explanation> --></html>
  return v;
}
