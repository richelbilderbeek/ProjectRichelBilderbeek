#include <cassert>
#include <cstring>

int main()
{
  const char source[] = "0123456789";

  const int length = std::strlen(source);
  assert(length == 10
    && "std::strlen does not count the trailing null terminator");

  char * const buffer = new char[ length + 1]; //Take '\0' into account
  std::strcpy(buffer,source);

  assert(std::strlen(buffer) == length
    && "Source and buffer must contain the same number of characters");

  assert(std::strcmp(source,buffer) == 0
    && "Source and buffer must contain the same characters");
}
