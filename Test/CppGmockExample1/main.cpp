#include <gmock/gmock.h>

TEST(MyTestCaseName,OneAndOneIsTwo)
{
  ASSERT_THAT(1 + 1,testing::Eq(2));
}

int main(int argc, char* argv[])
{
  testing::InitGoogleMock(&argc,argv);
  return RUN_ALL_TESTS();
}

/* Does not link:

/MyFolder/CppGmockExample1:
error while loading shared libraries: libgmock.so.0:
cannot open shared object file: No such file or directory

*/
