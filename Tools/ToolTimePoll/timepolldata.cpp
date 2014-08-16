#include "timepolldata.h"
#include "stopwatch.h"



ribi::ToolTimePoll::Data * ribi::ToolTimePoll::Data::m_instance = 0;

std::recursive_mutex ribi::ToolTimePoll::Data::m_mutex;

ribi::ToolTimePoll::Data::Data(const int n_options)
  : m_index(-1),
    m_times(n_options,0.0),
    m_stopwatch(new Stopwatch)
{

}

const std::vector<double> ribi::ToolTimePoll::Data::GetFractions() const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);
  std::vector<double> v = GetTimes(); //Recursion: need std::recursive_mutex
  const double sum_time = std::accumulate(v.begin(),v.end(),0.0);

  if (sum_time != 0.0)
  {
    std::for_each(v.begin(),v.end(),
      [sum_time](double& d) { d/= sum_time; } );

  }
  return v;
}

ribi::ToolTimePoll::Data * ribi::ToolTimePoll::Data::GetInstance()
{
  if (m_instance == 0)
  {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    //Double-lock idiom
    if (m_instance == 0)
    {
      m_instance = new Data;
    }
  }
  assert(m_instance);
  return m_instance;
}

const std::vector<double> ribi::ToolTimePoll::Data::GetTimes() const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);
  std::vector<double> times = m_times;
  if (m_index != -1)
  {
    assert(m_index >= 0);
    assert(m_index < static_cast<int>(times.size()));
    assert(m_stopwatch);
    times[m_index]+=m_stopwatch->elapsed();
  }
  return times;
}

void ribi::ToolTimePoll::Data::SetIndex(const int index)
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);
  if (m_index != -1)
  {
    assert(m_index >= 0);
    assert(m_index < static_cast<int>(m_times.size()));
    assert(m_stopwatch);
    m_times[m_index] += m_stopwatch->elapsed();
  }
  m_stopwatch.reset(new Stopwatch);
  m_index = index;
}
