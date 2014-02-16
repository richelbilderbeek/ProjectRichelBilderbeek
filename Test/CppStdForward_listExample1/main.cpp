#include <forward_list>
#include <iostream>
#include <iterator>

int main()
{
  //Initialize with an initializer list
  std::forward_list<int> my_list { 1 };
  //Add a zero at the beginning
  my_list.push_front(0);
  //Obtain an iterator to a position in between
  std::forward_list<int>::iterator my_iterator = my_list.begin();
  ++my_iterator;
  //Insert a two after the 1
  my_list.insert_after(my_iterator,2);
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
