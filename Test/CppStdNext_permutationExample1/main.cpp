#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  std::vector<int> v = {1,2,3};

  assert(std::is_sorted(v.begin(),v.end())
    && "The vector must be sorted to see all permutations");

  //Display std::vector
  std::cout << "Initial v: ";
  std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';

  //Obtain the next permutation
  while(std::next_permutation(v.begin(),v.end()))
  {
    //Display std::vector
    std::cout << "Next permutation: ";
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << '\n';
  }

  //Sort and reverse the std::vector
  std::sort(v.begin(),v.end());
  std::reverse(v.begin(),v.end());

  //Display std::vector
  std::cout << "Reverse-sorted v: ";
  std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';

  //Obtain the previous permutation
  while(std::prev_permutation(v.begin(),v.end()))
  {
    //Display std::vector
    std::cout << "Previous permutation: ";
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << '\n';
  }
}

/* Screen output

Initial v: 1 2 3
Next permutation: 1 3 2
Next permutation: 2 1 3
Next permutation: 2 3 1
Next permutation: 3 1 2
Next permutation: 3 2 1
Reverse-sorted v: 3 2 1
Previous permutation: 3 1 2
Previous permutation: 2 3 1
Previous permutation: 2 1 3
Previous permutation: 1 3 2
Previous permutation: 1 2 3
Press <RETURN> to close this window...

*/
