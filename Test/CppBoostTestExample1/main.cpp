#include <cstdlib>

#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>

void must_be_equal(int i, int j)
{
  BOOST_CHECK(i == j);
}

struct MyClass
{
  static void Test()
  {
    const int i = std::rand();
    BOOST_CHECK(i >= 0);
  }
};

bool my_init_function()
{
  {
    boost::unit_test::framework::master_test_suite().add(BOOST_TEST_CASE(&MyClass::Test));
  }
  {
    boost::unit_test::framework::master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 1, 1)));
    boost::unit_test::framework::master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 2, 2)));
    boost::unit_test::framework::master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 3, 3)));
  }
  return true;
}

int main(int argc, char* argv[])
{
  const int errors = boost::unit_test::unit_test_main( &my_init_function, argc, argv );
  std::cout << (errors ? "Not all tests succeeded" : "All tests succeeded!") << '\n';
}
