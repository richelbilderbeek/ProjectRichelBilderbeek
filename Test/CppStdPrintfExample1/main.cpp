#include <cstdio>
#include <string>

int main()
{
  {
    std::printf("Hello world\n");
  }
  {
    const int my_int = 42;
    std::printf("my_int: %i\n",my_int);
  }
  {
    const double my_double = 12.34;
    std::printf("my_double: %f\n",my_double);
  }
  {
    const char my_chars[] = "Hello world";
    std::printf("my_chars: %s\n",my_chars);
  }
  {
    const std::string my_string = "Hello world";
    std::printf("my_string: %s\n",my_string.c_str());
  }

}

/* Screen output:


*/
