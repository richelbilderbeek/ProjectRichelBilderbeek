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
  std::ifstream ifdata;
  ifdata.open(tasks_input_filename);
  int temparea1;
  int temparea2;
  int tempL;
  bool temptype;
  double temptol;
  ifdata >> temparea1;
  ifdata >> temparea2;
  ifdata >> tempL;
  temptype = true;
  int temptypeint;
  ifdata >> temptypeint;
  if (temptypeint == 0)
  {
    temptype = false;
  }
  ifdata >> temptol;
  while(!ifdata.eof())
  {
    tasks.push_back(Task(temparea1,temparea2,tempL,temptype,temptol));
    ifdata >> temparea1;
    ifdata >> temparea2;
    ifdata >> tempL;
    temptype = true;
    int temptypeint;
    ifdata >> temptypeint;
    if (temptypeint == 0)
    {
      temptype = false;
    }
    ifdata >> temptol;
  }
  ifdata.close();
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
