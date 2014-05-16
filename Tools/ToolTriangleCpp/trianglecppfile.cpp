#include "trianglecppfile.h"
/*

#include <cstring>
#include <cstdio>

#include "trianglecppglobals.h"

char * ribi::tricpp::readline(char * const string, FILE * const infile)
{
  char *result = nullptr;

  // Search for something that looks like a number.
  do {

    result = std::fgets(string, g_max_inputline_size, infile);


    if (!result) { //RJCB
      return nullptr;

    }
    // Skip anything that doesn't look like a number, a comment,
    //   or the end of a line.
    while ((*result != '\0') && (*result != '#')
           && (*result != '.') && (*result != '+') && (*result != '-')
           && ((*result < '0') || (*result > '9'))) {
      result++;
    }
  // If it's a comment or end of line, read another line and try again.
  } while ((*result == '#') || (*result == '\0'));
  return result;
}

*/
