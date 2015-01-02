#include <boost/locale.hpp>
#include <boost/math/constants/constants.hpp>

int main()
{
  const double pi = boost::math::constants::pi<double>();

  assert(std::locale().name() == "C");

  assert(boost::lexical_cast<std::string>(pi)[1] == '.' && "English");

  boost::locale::generator gen;
  std::locale::global(gen(""));
  std::locale::global(gen("en_US.UTF-8"));

  assert(std::locale().name() == "*");

  assert(boost::lexical_cast<std::string>(pi)[1] == '.' && "English");
}
