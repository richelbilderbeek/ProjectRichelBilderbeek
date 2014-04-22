#include <iostream>
#include <cstdio>
#include <string>

int main()
{
  for (int i=0; i!=10; ++i)
  {
    const std::string s = std::tmpnam(0);
    std::cout << s << '\n';
  }
}

/* Possible screen output:

\s1p4.
\s1p4.1
\s1p4.2
\s1p4.3
\s1p4.4
\s1p4.5
\s1p4.6
\s1p4.7
\s1p4.8
\s1p4.9
Press <RETURN> to close this window...

*/
