#ifndef NDEBUG
#include "task.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iterator>

#include "fileio.h"

void Task::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::fileio::FileIo;
  //operator==
  {
    const Task task1(12,23,34,0,0.1);
    const Task task2(12,23,34,0,0.1);
    assert(task1 == task2);
  }
  //operator!=
  {
    const Task task1(12,23,34,0,0.1);
    const Task task2( 0,23,34,0,0.1);
    const Task task3(12, 0,34,0,0.1);
    const Task task4(12,23, 0,0,0.1);
    const Task task5(12,23,34,1,0.1);
    const Task task6(12,23,34,0,0.0);
    assert(task1 != task2);
    assert(task1 != task3);
    assert(task1 != task4);
    assert(task1 != task5);
    assert(task1 != task6);
  }
  //stream operators
  {
    const Task task(12,23,34,0,0.1);
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << task;
    }
    std::ifstream f(filename);
    Task task_too(0,0,0,0,0);
    f >> task_too;
    assert(task == task_too);
    FileIo().DeleteFile(filename);
  }
  //ReadTasksFromFile
  {
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    std::vector<Task> tasks;
    tasks.push_back(Task(10,10,1,true,0.1));
    tasks.push_back(Task(20,10,1,true,0.1));
    tasks.push_back(Task(10,20,1,true,0.1));
    tasks.push_back(Task(10,10,2,true,0.1));
    tasks.push_back(Task(10,10,1,false,0.1));
    tasks.push_back(Task(10,10,1,true,0.01));
    {
      std::ofstream f(filename);
      std::copy(std::begin(tasks),std::end(tasks),std::ostream_iterator<Task>(f,"\n"));
    }
    const std::vector<Task> tasks_too = ReadTasksFromFile(filename);
    assert(tasks_too == tasks);
  }
}
#endif

