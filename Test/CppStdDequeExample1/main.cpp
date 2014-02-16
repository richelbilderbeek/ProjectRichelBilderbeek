#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
  std::deque<std::string> q;
  q.push_back("I am first");
  q.push_front("I get added in the front");
  q.push_back("I get added in the back");
  //Display q
  std::copy(q.begin(),q.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
}

/* Screen output:

I get added in the front
I am first
I get added in the back
Press <RETURN> to close this window...

*/
