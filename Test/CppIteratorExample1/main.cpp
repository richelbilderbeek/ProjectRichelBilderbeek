#include <iostream>
#include <list>

int main()
{
  std::list<int> my_list;
  my_list.push_back( 1);
  my_list.push_back( 4);
  my_list.push_back( 9);
  my_list.push_back(16);
  my_list.push_back(25);
  my_list.push_back(36);
  my_list.push_back(49);

  //Display the list (not preferred)
  typedef std::list<int>::const_iterator Iterator;
  const Iterator j = my_list.end();
  for (Iterator i = my_list.begin(); i!=j; ++i)
  {
    std::cout << *i << '\n';
  }
}

/* Screen output:

1
4
9
16
25
36
49
Press <RETURN> to close this window...

*/
