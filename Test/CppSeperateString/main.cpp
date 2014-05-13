#include <algorithm>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/split.hpp>
#include <boost/function.hpp>
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> SeperateString1(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> SeperateString2(
  const std::string& input,
  const char seperator)
{
  std::istringstream is(input);
  std::vector<std::string> v;
  for (
    std::string sub;
    std::getline(is, sub, seperator);
    v.push_back(sub))
  {
    //Empty for loop
  }
  return v;
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> SeperateString3(const std::string& input, const char& seperator)
{
  std::vector<std::string> v;
  typedef std::string::const_iterator Iterator;
  const Iterator end = input.end();
  Iterator i1 = input.begin();
  {
    //Copy until first comma
    Iterator i2 = std::find(i1,end,seperator);
    assert(i1!=i2);
    std::string s;
    std::copy(i1,i2,std::back_inserter(s));
    v.push_back(s);
    i1 = i2;
  }
  while (i1!=end)
  {
    //Copy from comma to (comma || end)
    Iterator i2 = std::find(i1 + 1,end,seperator);
    assert(i1!=i2);
    assert(i2 == end || *i2 == seperator);
    std::string s;
    std::copy(i1+1,i2,std::back_inserter(s));
    v.push_back(s);
    i1 = i2;
  }
  return v;
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> SeperateString4(std::string input, const char& seperator)
{
  assert(!input.empty());
  assert(input[0]!=seperator);
  assert(input[input.size()-1]!=seperator);

  std::vector<std::string> result;
  int pos = 0;
  while(pos<static_cast<int>(input.size()))
  {
    if (input[pos]==seperator)
    {
      const std::string found = input.substr(0,pos);
      result.push_back(found);
      input = input.substr(pos+1,input.size()-pos);
      pos = 0;
    }
    ++pos;
  }
  result.push_back(input);
  return result;
}

//From //From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> SeperateString5(
  const std::string& input,
  const std::string& seperator)
{
  std::vector<std::string> v;
  typedef std::string::const_iterator Iterator;
  const Iterator end = input.end();
  Iterator i1 = input.begin();
  {
    //Copy until first comma
    Iterator i2 = std::search(i1,end,seperator.begin(), seperator.end());
    assert(i1!=i2);
    std::string s;
    std::copy(i1,i2,std::back_inserter(s));
    v.push_back(s);
    i1 = i2;
  }
  while (i1!=end)
  {
    //Copy from comma to (comma || end)
    Iterator i2 = std::search(i1 + 1,end,seperator.begin(), seperator.end());
    assert(i1!=i2);
    assert(i2 == end || std::equal(seperator.begin(),seperator.end(),i2));
    std::string s;
    std::copy(i1+1,i2,std::back_inserter(s));
    v.push_back(s);
    i1 = i2;
  }
  return v;
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> SeperateString6(std::string input, const std::string& seperator)
{
  assert(!input.empty());
  assert(input.substr(0,seperator.size()) != seperator);
  assert(input.substr(input.size()-seperator.size(),seperator.size())!=seperator);
  std::vector<std::string> result;
  int pos = 0;
  while(pos<static_cast<int>(input.size()))
  {
    if (input.substr(pos,seperator.size())==seperator)
    {
      const std::string found = input.substr(0,pos);
      result.push_back(found);
      input = input.substr(pos+seperator.size(),input.size()-pos);
      pos = 0;
    }
    ++pos;
  }
  result.push_back(input);
  return result;
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
void TestSeperateStringSeperatorIsChar(boost::function<std::vector<std::string>(const std::string&, const char)> f)
{
  {
    //#define THESE_WILL_FAIL_AND_SHOULD_FAIL
    #ifdef THESE_WILL_FAIL_AND_SHOULD_FAIL
    //Empty
    const std::vector<std::string> v1 = f("",',');
    //Seperator only
    const std::vector<std::string> v2 = f(",",',');
    //Single input, leading seperator
    const std::vector<std::string> v3 = f(",a",',');
    //Single input, trailing seperator
    const std::vector<std::string> v4 = f("a,",',');
    //Two inputs, leading seperator
    const std::vector<std::string> v5 = f(",a,a",',');
    //Two inputs, trailing seperator
    const std::vector<std::string> v6 = f("a,a,",',');
    #endif
  }

  { //Single input, seperator of type char
    const std::vector<std::string> v = f("a",',');
    assert(v[0]=="a");
  }
  { //Two inputs, seperator of type char
    const std::vector<std::string> v = SeperateString3("a,b",',');
    assert(v[0]=="a");
    assert(v[1]=="b");
  }
  { //Five inputs, seperator of type char
    const std::vector<std::string> v = SeperateString3("a,bb,ccc,dddd,eeeee",',');
    assert(v[0]=="a");
    assert(v[1]=="bb");
    assert(v[2]=="ccc");
    assert(v[3]=="dddd");
    assert(v[4]=="eeeee");
  }
  { //Three inputs, of which one empty, seperator of type char
    const std::vector<std::string> v = SeperateString3("a, ,ccc",',');
    assert(v[0]=="a");
    assert(v[1]==" ");
    assert(v[2]=="ccc");
  }
}



//From http://www.richelbilderbeek.nl/CppSeperateString.htm
void TestSeperateStringSeperatorIsString(boost::function<std::vector<std::string>(const std::string&, const std::string&)> f)
{
  {
    //#define THESE_WILL_FAIL_AND_SHOULD_FAIL
    #ifdef THESE_WILL_FAIL_AND_SHOULD_FAIL
    //Empty
    const std::vector<std::string> v1 = f("",",");
    //Seperator only
    const std::vector<std::string> v2 = f(",",",");
    //Single input, leading seperator
    const std::vector<std::string> v3 = f(",a",",");
    //Single input, trailing seperator
    const std::vector<std::string> v4 = f("a,",",");
    //Two inputs, leading seperator
    const std::vector<std::string> v5 = f(",a,a",",");
    //Two inputs, trailing seperator
    const std::vector<std::string> v6 = f("a,a,",",");
    #endif
  }
  { //Single input, seperator of type std::string
    const std::vector<std::string> v = f("a",",");
    assert(v[0]=="a");
  }
  { //Two inputs, seperator of type std::string
    const std::vector<std::string> v = f("a,b",",");
    assert(v[0]=="a");
    assert(v[1]=="b");
  }
  { //Five inputs, seperator of type std::string
    const std::vector<std::string> v = f("a,bb,ccc,dddd,eeeee",",");
    assert(v[0]=="a");
    assert(v[1]=="bb");
    assert(v[2]=="ccc");
    assert(v[3]=="dddd");
    assert(v[4]=="eeeee");
  }
  { //Three inputs, of which one empty, seperator of type std::string
    const std::vector<std::string> v = f("a, ,ccc",",");
    assert(v[0]=="a");
    assert(v[1]==" ");
    assert(v[2]=="ccc");
  }
}

int main()
{
  TestSeperateStringSeperatorIsChar(SeperateString1);
  TestSeperateStringSeperatorIsChar(SeperateString2);
  TestSeperateStringSeperatorIsChar(SeperateString3);
  TestSeperateStringSeperatorIsChar(SeperateString4);
  TestSeperateStringSeperatorIsString(SeperateString5);
  TestSeperateStringSeperatorIsString(SeperateString6);
}
