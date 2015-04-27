#include "task.h"

#include <cassert>
#include <fstream>
#include "fileio.h"

Task::Task(
  int any_area1,
  int any_area2,
  int any_L,
  bool any_type,
  double any_tol
) : area1{any_area1},
    area2{any_area2},
    L{any_L},
    type{any_type},
    tol{any_tol}
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
