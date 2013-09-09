#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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
#pragma GCC diagnostic pop

const ribi::About ribi::kalman::KalmanFiltererMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "KalmanFilterer",
    "tool to work with Kalman filters",
    "the 17th of July 2013",
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

const std::string ribi::kalman::KalmanFiltererMenuDialog::GetVersion()
{
  return "1.15";
}

const std::vector<std::string> ribi::kalman::KalmanFiltererMenuDialog::GetVersionHistory()
{
  const std::vector<std::string> v {
    "2013-04-28: version 1.0: initial Qt4 and Boost 1.49.0 version that started from CppKalmanFilterExample13",
    "2013-05-01: version 1.1: added plotting, added steady-state Kalman filter",
    "2013-05-02: version 1.2: fixed messed-up graphs and calculation displayal",
    "2013-05-03: version 1.3: improved parameters GUI and use",
    "2013-05-06: version 1.4: prepared architecture for expansion",
    "2013-05-16: version 1.5: use of model/view architecture, preparations for adding fixed-lag-smoother Kalman filter",
    "2013-05-28: version 1.6: added loading (from DokuWiki) and saving (to DokuWiki and HTML) of parameters",
    "2013-05-28: version 1.7: added possibility to save graphs to file",
    "2013-06-13: version 1.8: fixed bug in parameter tables, allow to view data as a table",
    "2013-06-14: version 1.9: allow to copy data from table",
    "2013-06-17: version 1.10: removed useless examples",
    "2013-06-27: version 1.11: added gaps-filled white noise system, added versioning to parameter files for backwards compatibility",
    "2013-07-01: version 1.12: added the constants pi and tau to function parser, context can be saved to file, tables are displayed correctly",
    "2013-07-05: version 1.13: added simple statistics",
    "2013-07-08: version 1.14: display statistics and value tables correctly, allow editing of context, tables resize to the number of rows",
    "2013-07-17: version 1.15: allow copying from and pasting to parameter tables, transitioned to Qt5, GCC 4.8.0 and Boost 1.54.0, able to crosscompile again"
  };
  return v;
}
