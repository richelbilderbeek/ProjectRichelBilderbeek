#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

///DangerDoNotDoThis demonstrates that if a non-existing file is read,
///the program will do this without warning and infinitely
void DangerDoNotDoThis()
{
  //Assure that the file does not exist
  const std::string filename { "tmp.txt" };
  std::remove(filename.c_str());

  //'Open' the nonexisting file
  std::ifstream f(filename.c_str());

  //This test will prevent all nasty things from happening!
  //assert(f.is_open());

  //Read until the end of the (non-existing) file. For a non-existing file
  //this will read infinitely
  for (int i=0; !f.eof(); ++i)
  {
    std::string s;
    std::getline(f,s);
    //Display a dot and s (which will be empty) without a newline
    //This will cause the whole screen to fill up with dots
    std::cout << "." << s << std::flush;
  }

}

int main()
{
  DangerDoNotDoThis();
}

/* Screen output (copied after breaking the program):

................................................................................
................................................................................
................................................Press <RETURN> to close this win
dow...

*/
