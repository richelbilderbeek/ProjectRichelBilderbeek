#include <cstdlib>

int main()
{
  std::system("dir *.* > output.txt");
  std::system("type output.txt"); //On Windows
}

/* Screen output:

 Volume in drive D is DATA
 Volume Serial Number is 6E49-4539

 Directory of D:\Projects\Test\build-CppStdSystemExample1-Desktop_Qt_5_1_1_MinGW
_32bit-Debug

03/20/2014  03:39 PM    <DIR>          .
03/20/2014  03:39 PM    <DIR>          ..
03/20/2014  03:40 PM    <DIR>          debug
03/20/2014  03:39 PM            11,221 Makefile
03/20/2014  03:39 PM             7,666 Makefile.Debug
03/20/2014  03:39 PM             7,740 Makefile.Release
03/20/2014  03:41 PM                 0 output.txt
03/20/2014  03:39 PM    <DIR>          release
               4 File(s)         26,627 bytes
               4 Dir(s)  202,344,755,200 bytes free
Press <RETURN> to close this window...

*/
