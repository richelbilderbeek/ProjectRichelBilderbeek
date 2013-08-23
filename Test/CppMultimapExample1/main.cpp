#include <iostream>
#include <map>
#include <string>

int main()
{
  typedef std::multimap<std::string,int> Container;
  typedef Container::const_iterator Iterator;

  Container questions;

  questions.insert(std::make_pair("A prime number between 5 and 10",7));
  questions.insert(std::make_pair("A prime number between 10 and 15",11));
  questions.insert(std::make_pair("A prime number between 10 and 15",13));
  questions.insert(std::make_pair("A prime number between 10 and 20",11));
  questions.insert(std::make_pair("A prime number between 10 and 20",13));
  questions.insert(std::make_pair("A prime number between 10 and 20",17));
  questions.insert(std::make_pair("A prime number between 10 and 20",19));
  questions.insert(std::make_pair("A prime number between 20 and 25",23));

  const std::pair<Iterator,Iterator> answers
    = questions.equal_range("A prime number between 10 and 20");

  for (Iterator i = answers.first; i!= answers.second; ++i)
  {
    std::cout << i->second << '\n';
  }
}
