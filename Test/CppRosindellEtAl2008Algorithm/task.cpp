#include "task.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

Task::Task(
  const int survey_area_width,
  const int survey_area_length,
  const int dispersal_distance,
  const bool dispersal_kernel_type,
  const double tolerance
) : m_survey_area_width{survey_area_width},
    m_survey_area_length{survey_area_length},
    m_dispersal_distance{dispersal_distance},
    m_dispersal_kernel_type{dispersal_kernel_type},
    m_tolerance{tolerance}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<Task> ReadTasksFromFile(
  const std::string& tasks_input_filename
)
{
  using ribi::fileio::FileIo;
  assert(
    FileIo().IsRegularFile(tasks_input_filename)
  );

  std::vector<Task> tasks;
  std::ifstream f(tasks_input_filename);
  while(!f.eof())
  {
    Task task(0,0,0,0,0);
    f >> task;
    tasks.emplace_back(task);
  }
  if (!tasks.empty()) { tasks.pop_back(); }
  return tasks;
}

std::ostream& operator<<(std::ostream& os, const Task& task)
{
  os
    << task.m_survey_area_width << " "
    << task.m_survey_area_length << " "
    << task.m_dispersal_distance << " "
    << task.m_dispersal_kernel_type << " "
    << task.m_tolerance
  ;
  return os;
}

std::istream& operator>>(std::istream& is, Task& task)
{
  int area_width;
  int area_height;
  int dispersal_distance;
  bool dispersal_kernel_type;
  double tolerance;
  is >> area_width;
  is >> area_height;
  is >> dispersal_distance;
  dispersal_kernel_type = true;
  int temptypeint;
  is >> temptypeint;
  if (temptypeint == 0)
  {
    dispersal_kernel_type = false;
  }
  is >> tolerance;
  task = Task(
    area_width,
    area_height,
    dispersal_distance,
    dispersal_kernel_type,
    tolerance
  );
  return is;
}

bool operator==(const Task& lhs, const Task& rhs) noexcept
{
  return
       lhs.GetDispersalDistance()   == rhs.GetDispersalDistance()
    && lhs.GetDispersalKernelType() == rhs.GetDispersalKernelType()
    && lhs.GetSurveyAreaLength()    == rhs.GetSurveyAreaLength()
    && lhs.GetSurveyAreaWidth()     == rhs.GetSurveyAreaWidth()
    && lhs.GetTolerance()           == rhs.GetTolerance()
  ;
}

bool operator!=(const Task& lhs, const Task& rhs) noexcept
{
  return !(lhs == rhs);
}
