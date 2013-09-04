#include <cassert>
#include <stdexcept>

//Copied from
// * Bjarne Stroustrup. The C++ Programming Language (4th edition). 2013.
//   ISBN: 978-0-321-56384-2. Chapter 11.5: Explicit type conversion. page 299.
template <class Target, class Source>
Target narrow_cast(Source v)
{
  auto r = static_cast<Target>(v);
  if (static_cast<Source>(r)!=v)
    throw std::runtime_error("narrow_cast<>() failed");
  return r;
}

int main()
{
  try
  {
    narrow_cast<int>(12.34);
    assert(!"Incorrect conversion from double to int should be detected by narrow_cast");
  }
  catch (std::runtime_error& e)
  {
    //OK
  }
}
