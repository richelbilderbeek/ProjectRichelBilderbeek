#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>

int main()
{
  const std::string s = "ABXDEF";

  //C style way to find a character in a string
  const char * const c = std::strchr(&s[0],'X');
  assert(*(c-1)=='B');
  assert(*(c+1)=='D');

  //Similar C++ style way to find a character in a string
  const std::string::const_iterator i
    = std::find(s.begin(),s.end(),'X');
  assert(*(i-1)=='B');
  assert(*(i+1)=='D');
}
