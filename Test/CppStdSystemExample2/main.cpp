#include <cstdlib>

int main()
{
  std::system("mkdir tmp & cd tmp && dir *.* > output.txt && type output.txt"); //On Windows
}

/* Screen output:

A subdirectory or file tmp already exists.
 Volume in drive D is DATA
 Volume Serial Number is 6E49-4539

 Directory of D:\Projects\Test\build-CppStdSystemExample2-Desktop_Qt_5_1_1_MinGW
_32bit-Debug\tmp

03/20/2014  03:43 PM    <DIR>          .
03/20/2014  03:43 PM    <DIR>          ..
03/20/2014  03:43 PM                 0 output.txt
               1 File(s)              0 bytes
               2 Dir(s)  202,344,558,592 bytes free
Press <RETURN> to close this window...

*/
