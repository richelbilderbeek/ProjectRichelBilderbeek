#include "testtimer.h"

#include <iostream>

#include <boost/timer.hpp>

namespace ribi {

struct TestTimerImpl
{
  TestTimerImpl(
    const std::string& function_name,
    const std::string& file_name,
    const double max_time_sec
  )
    : m_file_name{file_name},
      m_function_name{function_name},
      m_max_time_sec{max_time_sec},
      m_timer{}
  {

  }

  const std::string m_file_name;
  const std::string m_function_name;
  const double m_max_time_sec;
  boost::timer m_timer;
};

} //~namespace ribi


ribi::TestTimer::TestTimer(
  const std::string& function_name,
  const std::string& file_name,
  const double max_time_sec
) noexcept
  : m_impl(new TestTimerImpl(function_name,file_name,max_time_sec))
{
  std::clog
    << "START: "
    << m_impl->m_file_name
    << ','
    << m_impl->m_function_name
    << std::endl
  ;
}

ribi::TestTimer::~TestTimer() noexcept
{
  const double elapsed_secs = m_impl->m_timer.elapsed();
  if (elapsed_secs > m_impl->m_max_time_sec)
  {
    std::clog
      << "FUNCTION '"
      << m_impl->m_function_name
      << "' IN FILE '"
      << m_impl->m_file_name
      << "' TOOK TOO LONG"
      << std::endl
    ;
    std::exit(0);
  }
  std::clog
    << "DONE: "
    << m_impl->m_file_name
    << ','
    << m_impl->m_function_name
    << " ("
    << elapsed_secs
    << " seconds)"
    << std::endl
  ;
}

std::string ribi::TestTimer::GetVersion() noexcept
{
  return "1.0";
}
std::vector<std::string> ribi::TestTimer::GetVersionHistory() noexcept
{
  return {
    "2014-08-02: version 1.0: initial version"
  };
}
