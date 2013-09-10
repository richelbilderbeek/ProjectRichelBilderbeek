#include <iostream>
#include <iterator>
#include <list>

int main()
{
  std::list<int> my_list;
  //Add a two at the end
  my_list.push_back(2);
  //Add a zero at the beginning
  my_list.push_front(0);
  //Obtain an iterator to a position in between
  std::list<int>::iterator my_iterator = my_list.begin();
  ++my_iterator;
  //Insert a one in between
  my_list.insert(my_iterator,1);
  //Display the list
  std::copy(my_list.begin(),my_list.end(),
    std::ostream_iterator<int>(std::cout,"\n"));
}

/* Screen output:

0
1
2
Press <RETURN> to close this window...

*/
