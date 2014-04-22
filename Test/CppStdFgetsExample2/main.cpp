#include <cassert>
#include <fstream>
#include <iostream>

int main()
{
  const std::string filename = "tmp.txt";
  {
    std::ofstream file(filename.c_str());
    const int zero = 0;
    file
      << zero << '\n'
      << 0 << '\n'
      << 1 << '\n'
      << 2 << '\n'
      << 3 << '\n'
      << 4 << '\n'
      << 5 << '\n'
      << 6 << '\n'
      << 7 << '\n'
      << 8 << '\n'
      << 9 << '\n'
      << 0 << '\n'
      << zero;
  }

  std::FILE* const file = std::fopen(filename.c_str(),"r");
  const std::FILE * const file_before = file;

  const int buffer_size = 8;
  char buffer[buffer_size];
  for (int i=0; ; ++i)
  {
    if (!std::fgets(buffer, buffer_size, file)) break;
    std::cout << i << ": <before>" << buffer << "<after>" << '\n';

    assert(file_before == file
      && "Magic: the file is read sequential, yet file remains the same");
  }
}

/* Screen output

0: <before>0
<after>
1: <before>0
<after>
2: <before>1
<after>
3: <before>2
<after>
4: <before>3
<after>
5: <before>4
<after>
6: <before>5
<after>
7: <before>6
<after>
8: <before>7
<after>
9: <before>8
<after>
10: <before>9
<after>
11: <before>0
<after>
12: <before>0<after>
Press <RETURN> to close this window...


*/
