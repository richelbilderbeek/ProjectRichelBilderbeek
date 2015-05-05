//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#include "task.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

Task::Task(
  const int survey_area_width,
  const int survey_area_length,
  const int dispersal_distance,
  const DispersalKernel dispersal_kernel_type,
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
    Task task(0,0,0,DispersalKernel::square,0);
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
  int area_width = 0;
  int area_height = 0;
  int dispersal_distance = 0;
  DispersalKernel dispersal_kernel_type = DispersalKernel::square;
  double tolerance = 0.0;
  is
    >> area_width
    >> area_height
    >> dispersal_distance
    >> dispersal_kernel_type
    >> tolerance
  ;
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
