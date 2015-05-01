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
