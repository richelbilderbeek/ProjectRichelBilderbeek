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
#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

#include "dispersalkernel.h"

struct Task
{
  ///tolerance: if tolerance equals 0.01, then result is correct to approximately 0.5%
  Task(
    const int survey_area_width,
    const int survey_area_length,
    const int dispersal_distance,
    const DispersalKernel dispersal_kernel_type,
    const double tolerance
  );
  int GetSurveyAreaWidth() const noexcept { return m_survey_area_width; }
  int GetSurveyAreaLength() const noexcept { return m_survey_area_length; }
  int GetDispersalDistance() const noexcept { return m_dispersal_distance; }
  DispersalKernel GetDispersalKernelType() const noexcept { return m_dispersal_kernel_type; }
  double GetTolerance() const noexcept { return m_tolerance; }
  int m_survey_area_width;
  int m_survey_area_length;
  int m_dispersal_distance;
  DispersalKernel m_dispersal_kernel_type;
  double m_tolerance;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::vector<Task> ReadTasksFromFile(
  const std::string& tasks_input_filename = "tasksfile.txt"
);

std::ostream& operator<<(std::ostream& os, const Task& task);
std::istream& operator>>(std::istream& os, Task& task);

bool operator==(const Task& lhs, const Task& rhs) noexcept;
bool operator!=(const Task& lhs, const Task& rhs) noexcept;

#endif // TASK_H
