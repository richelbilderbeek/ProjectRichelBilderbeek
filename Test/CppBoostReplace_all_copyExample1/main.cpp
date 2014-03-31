#include <cassert>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/replace.hpp>
#pragma GCC diagnostic pop

int main()
{
  const std::string s = "A*B*C*D*E*A*B*C*D*E";
  const std::string t = boost::algorithm::replace_all_copy(s,"*B","*B");
  assert(t == s);
  const std::string u = boost::algorithm::replace_all_copy(t,"*C","*X");
  assert(u == "A*B*X*D*E*A*B*X*D*E");
}

