#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

///Example adapted from http://www.boost.org/doc/libs/1_54_0/doc/html/xpressive/user_s_guide.html
int main()
{
  const std::string hello( "hello world!" );

  const boost::xpressive::sregex rex = boost::xpressive::sregex::compile( "(\\w+) (\\w+)!" );
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( hello, what, rex ) )
  {
    std::cout << what[0] << '\n'; // whole match
    std::cout << what[1] << '\n'; // first capture
    std::cout << what[2] << '\n'; // second capture
  }
}
