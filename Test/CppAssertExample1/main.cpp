#include <cassert>
#include <iostream>

int main()
{
  const double numerator = 1.0;
  const double denominator = 0.0;
  assert(denominator != 0.0);
  const double result = numerator / denominator;
  std::cout << result << std::endl;
}

/* Screen output with 'Projects | Run | Run in terminal' checked

Assertion failed!

Program: E:\Projects\Test\build-CppAssert-Desktop_Qt_5_1_0_MinGW_32bit-Debug\deb
ug\CppAssert.exe
File: ../CppAssert/main.cpp, Line 7

Expression: denominator != 0.0

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.
Press <RETURN> to close this window...

*/

/* Screen output with 'Projects | Run | Run in terminal' unchecked

Starting E:\Projects\Test\build-CppAssert-Desktop_Qt_5_1_0_MinGW_32bit-Debug\debug\CppAssert.exe...
Cannot retrieve debugging output.

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.
E:\Projects\Test\build-CppAssert-Desktop_Qt_5_1_0_MinGW_32bit-Debug\debug\CppAssert.exe exited with code 3

*/
