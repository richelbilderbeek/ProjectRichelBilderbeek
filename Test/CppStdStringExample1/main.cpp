#include <cassert>
#include <string>

int main()
{
  {
    const std::string s { "123" };
    assert(s == "123");
    assert("123" == s);
  }
  {
    //const std::string s { "123" + "456" }; //Won't compile
    const std::string s { std::string("123") + "456" };
    assert(s == "123456");
    assert("123456" == s);
  }
}
