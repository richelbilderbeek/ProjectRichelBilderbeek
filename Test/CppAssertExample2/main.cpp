#include <cassert>
#include <csignal>
#include <cstdlib>
#include <iostream>

void onAbort(int)
{
  std::exit(1);
}

int main()
{
  //Connect the abort signal to the OnAbort, to obtain informative
  //screen output with 'Projects | Run | Run in terminal' unchecked
  std::signal(SIGABRT,onAbort);

  const double numerator = 1.0;
  const double denominator = 0.0;
  assert(denominator != 0.0);
  const double result = numerator / denominator;
  std::cout << result << std::endl;
}

/* Screen output with 'Projects | Run | Run in terminal' checked

Assertion failed!

Program: E:\Projects\Test\build-CppAssertExample2-Desktop_Qt_5_1_0_MinGW_32bit-D
ebug\debug\CppAssertExample2.exe
File: ../CppAssertExample2/main.cpp, Line 19

Expression: denominator != 0.0

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.
Press <RETURN> to close this window...

*/



/* Screen output with 'Projects | Run | Run in terminal' unchecked

Starting E:\Projects\Test\build-CppAssertExample2-Desktop_Qt_5_1_0_MinGW_32bit-Debug\debug\CppAssertExample2.exe...
Cannot retrieve debugging output.

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.
Assertion failed!

Program: E:\Projects\Test\build-CppAssertExample2-Desktop_Qt_5_1_0_MinGW_32bit-Debug\debug\CppAssertExample2.exe
File: ../CppAssertExample2/main.cpp, Line 27

Expression: denominator != 0.0
E:\Projects\Test\build-CppAssertExample2-Desktop_Qt_5_1_0_MinGW_32bit-Debug\debug\CppAssertExample2.exe exited with code 1

*/
