#include <cstdlib>

#define BOOST_TEST_DYN_LINK
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>
#pragma GCC diagnostic pop

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
  using boost::unit_test::framework::master_test_suite;
  //Add MyClass::Test as a test case
  {
    master_test_suite().add(BOOST_TEST_CASE(&MyClass::Test));
  }
  //Test integers being equal to themselves
  {
    master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 1, 1)));
    master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 2, 2)));
    master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 3, 3)));
    master_test_suite().add(BOOST_TEST_CASE(boost::bind(&must_be_equal, 3, 4))); //Error added on purpose
  }
  return true;
}

int main(int argc, char* argv[])
{
  const int errors = boost::unit_test::unit_test_main( &my_init_function, argc, argv );
  std::cout << (errors ? "Not all tests succeeded" : "All tests succeeded!") << '\n';
}

/* Screen output:

Starting /home/richel/GitHubs/richelbilderbeek/develop/ProjectRichelBilderbeek/Test/build-CppBoostTestExample1-Desktop-Debug/CppBoostTestExample1...
Running 5 test cases...
../CppBoostTestExample1/main.cpp(13): error in "boost::bind(&must_be_equal, 3, 4)": check i == j failed
Not all tests succeeded

*** 1 failure detected in test suite "Master Test Suite"
/home/richel/GitHubs/richelbilderbeek/develop/ProjectRichelBilderbeek/Test/build-CppBoostTestExample1-Desktop-Debug/CppBoostTestExample1 exited with code 0

*/
