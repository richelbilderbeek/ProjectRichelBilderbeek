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
    int any_area1,
    int any_area2,
    int any_L,
    bool any_type,
    double any_tol
  );

  int area1;
  int area2;
  int L;
  bool type;
  double tol;
};

std::vector<Task> ReadTasksFromFile(
  const std::string& tasks_input_filename = "tasksfile.txt"
);

std::ostream& operator<<(std::ostream& os, const Task& task);


#endif // TASK_H
