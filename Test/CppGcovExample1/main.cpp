#include <iostream>

//Example adapted from https://en.wikipedia.org/wiki/Gcov
int main()
{
  for (int i = 1; i!=10; ++i)
  {
    if (i % 3 == 0)
    {
      std::cout << i << " is divisible by 3\n";
    }
    if (i % 11 == 0)
    {
      std::cout << i << " is divisible by 11\n";
    }
  }
}

/* Screen output:

3 is divisible by 3
6 is divisible by 3
9 is divisible by 3
Press <RETURN> to close this window...

*/

//After running the program, go to the executable's folder and type
//
// gcov main.gcda
//
// or
//
// gcov main.gcdo
//
// results in the following main.cpp.gcov:
//
#ifdef SHOW_UNMODIFIED_CONTENT

        -:    0:Source:../CppGcovExample1/main.cpp
        -:    0:Graph:main.gcno
        -:    0:Data:main.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:/*EOF*/
        -:    2:/*EOF*/
        -:    3:/*EOF*/
        1:    4:/*EOF*/
        -:    5:/*EOF*/
       10:    6:/*EOF*/
        -:    7:/*EOF*/
        9:    8:/*EOF*/
        -:    9:/*EOF*/
        3:   10:/*EOF*/
        -:   11:/*EOF*/
        9:   12:/*EOF*/
        -:   13:/*EOF*/
    #####:   14:/*EOF*/
        -:   15:/*EOF*/
        -:   16:/*EOF*/
        4:   17:/*EOF*/

#endif
