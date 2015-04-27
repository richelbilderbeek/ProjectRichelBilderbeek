#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

// read in list of tasks
// tasks file should consists of rows each of which has 5 entries
// 1.) width of survey area
// 2.) length of survey area
// 3.) dispersal distance
// 4.) dispersal kernel type (square if 0 normal if 1)
// 5.) tolerance (if 0.01 then result is correct to ±0.5%)
struct Task
{
  Task(
    const int survey_area_width,
    const int survey_area_length,
    const int dispersal_distance,
    const bool dispersal_kernel_type,
    const double tolerance
  );

  int m_survey_area_width;
  int m_survey_area_length;
  int m_dispersal_distance;
  bool m_dispersal_kernel_type;
  double m_tolerance;
};

std::vector<Task> ReadTasksFromFile(
  const std::string& tasks_input_filename = "tasksfile.txt"
);

std::ostream& operator<<(std::ostream& os, const Task& task);


#endif // TASK_H
