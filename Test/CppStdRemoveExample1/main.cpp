#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{
  //Remove elements from a std::vector
  //using std::remove from algorithm.h
  {
    std::vector<int> v;
    v.push_back(0);
    v.push_back(42);
    v.push_back(1);
    v.push_back(42);
    v.push_back(2);
    v.push_back(42);
    v.push_back(3);

    std::cout << "v before std::remove: ";
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;

    const std::vector<int>::iterator new_end
        = std::remove(v.begin(),v.end(),42);

    std::cout << "v after std::remove, before erase: ";
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;

    v.erase(new_end,v.end());

    std::cout << "v after erase: ";
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
  }

  //Remove a file using std::remove in cstdio.h
  {
    //Remove the possibly existing file
    std::remove("test.txt");
    //Try to delete the non-existing test.txt file
    const bool deletion_failed = std::remove("test.txt");
    assert(deletion_failed);
  }
  {
    //Create the file test.txt
    {
      std::ofstream f("test.txt");
      //Closes the file when f goes out of scope,
      //std::remove fails when file is still open
    }
    //Delete it again
    const bool deletion_failed = std::remove("test.txt");
    assert(!deletion_failed);
  }
}

/* Screen output:

v before std::remove: 0 42 1 42 2 42 3
v after std::remove, before erase: 0 1 2 3 2 42 3
v after erase: 0 1 2 3
Press <RETURN> to close this window...

*/
