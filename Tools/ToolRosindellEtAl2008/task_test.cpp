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
    const Task task1(12,23,34,DispersalKernel::square,0.1);
    const Task task2(12,23,34,DispersalKernel::square,0.1);
    assert(task1 == task2);
  }
  //operator!=
  {
    const Task task1(12,23,34,DispersalKernel::square,0.1);
    const Task task2( 0,23,34,DispersalKernel::square,0.1);
    const Task task3(12, 0,34,DispersalKernel::square,0.1);
    const Task task4(12,23, 0,DispersalKernel::square,0.1);
    const Task task5(12,23,34,DispersalKernel::normal,0.1);
    const Task task6(12,23,34,DispersalKernel::square,0.0);
    assert(task1 != task2);
    assert(task1 != task3);
    assert(task1 != task4);
    assert(task1 != task5);
    assert(task1 != task6);
  }
  //stream operators
  {
    const Task task(12,23,34,DispersalKernel::square,0.1);
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << task;
    }
    std::ifstream f(filename);
    Task task_too(0,0,0,DispersalKernel::square,0);
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
    tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(20,10,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,20,1,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,10,2,DispersalKernel::normal,0.1));
    tasks.push_back(Task(10,10,1,DispersalKernel::square,0.1));
    tasks.push_back(Task(10,10,1,DispersalKernel::normal,0.01));
    {
      std::ofstream f(filename);
      std::copy(std::begin(tasks),std::end(tasks),std::ostream_iterator<Task>(f,"\n"));
    }
    const std::vector<Task> tasks_too = ReadTasksFromFile(filename);
    assert(tasks_too == tasks);
  }
}
#endif

