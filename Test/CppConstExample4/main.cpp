#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

//Non-const vector to non-const pointer to non-const int
void nnn(std::vector<boost::shared_ptr<int>>& v)
{
  v.pop_back();
  v.back() = nullptr;
  *v.back() = 42;
}

//Const vector to non-const pointer to non-const int
void cnn(const std::vector<boost::shared_ptr<int>>& v)
{
  //v.pop_back();
  //v.back() = nullptr;
  *v.back() = 42;
}

//Non-const vector to const pointer to non-const int
//Useless: cannot read
void ncn(std::vector<const boost::shared_ptr<int>>& /* v */)
{
  //v.pop_back();
  //v.back() = nullptr;
  //*v.back() = 42;
  //assert(v.empty() || !v.empty()); //Always true, compiler happy
}

//Const vector to const pointer to non-const int
//Useless: cannot read
void ccn(const std::vector<const boost::shared_ptr<int>>& /* v */)
{
  //v.pop_back();
  //v.back() = nullptr;
  //*v.back() = 42;
  //assert(v.empty() || !v.empty()); //Always true, compiler happy
}

//Non-const vector to non-const pointer to const int
void nnc(std::vector<boost::shared_ptr<const int>>& v)
{
  v.pop_back();
  v.back() = nullptr;
  //*v.back() = 42;
}

//Const vector to non-const pointer to const int
//True read-only
void cnc(const std::vector<boost::shared_ptr<const int>>& v)
{
  //v.pop_back();
  //v.back() = nullptr;
  //*v.back() = 42;
  assert(v.empty() || !v.empty()); //Always true, compiler happy
}

//Non-const vector to const pointer to const int
//Useless: cannot read
void ncc(std::vector<const boost::shared_ptr<const int>>& /* v */)
{
  //v.pop_back();
  //v.back() = nullptr;
  //*v.back() = 42;
  //assert(v.empty() || !v.empty()); //Always true, compiler happy
}

//Const vector to const pointer to const int
//Useless: cannot read
void ccc(const std::vector<const boost::shared_ptr<const int>>& /* v */)
{
  //v.pop_back();
  //v.back() = nullptr;
  //*v.back() = 42;
  //assert(v.empty() || !v.empty()); //Always true, compiler happy
}

int main()
{
  //Nothing to see here
}
