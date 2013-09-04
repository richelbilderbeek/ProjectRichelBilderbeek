#include <exception>
#include <iostream>

struct MyException : public std::exception
{
  const char * what () const throw ()
  {
    return "Bilderbikkel was here";
  }
};

void Fire()
{
  throw MyException();
}

int main()
{
  try
  {
    Fire();
  }
  catch(MyException& e)
  {
    std::cout
      << "MyException caught: '"
      << e.what()
      << "'\n";
  }
  catch(std::exception& e)
  {
    //Other errors, shown for completeness
  }
}

/* Screen output:

MyException caught: 'Bilderbikkel was here'
Press <RETURN> to close this window...

*/
