//Example adapted from en.cppreference.com/w/cpp/io/c/fgets

#include <cstdio>
#include <cstdlib>
#include <iostream>

int main()
{
  std::FILE* const file = std::tmpfile();

  std::fputs("Alan Turing\n", file);
  std::fputs("John von Neumann\n", file);
  std::fputs("Alonzo Church\n", file);

  std::rewind(file);

  const int buffer_size = 8;
  char buffer[buffer_size];
  while (std::fgets(buffer, buffer_size, file) != NULL)
  {
    std::cout << "<before>" << buffer << "<after>" << '\n';
  }
}

/* Screen output

<before>Alan Tu<after>
<before>ring
<after>
<before>John vo<after>
<before>n Neuma<after>
<before>nn
<after>
<before>Alonzo <after>
<before>Church
<after>
Press <RETURN> to close this window...

*/
