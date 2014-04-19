#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct NoConstructor
{
  ~NoConstructor() {}
  private:
  NoConstructor() {}

  friend boost::shared_ptr<      NoConstructor> boost::make_shared<      NoConstructor>();
  friend boost::shared_ptr<const NoConstructor> boost::make_shared<const NoConstructor>();
};

struct NoDestructor
{
  NoDestructor() {}
  private:
  ~NoDestructor() {}

  friend class boost::detail::sp_ms_deleter<      NoDestructor>;
  friend class boost::detail::sp_ms_deleter<const NoDestructor>;
};


int main()
{
  {
    const auto p = boost::make_shared<const NoConstructor>();
    assert(p);
  }
  {
    const auto p = boost::make_shared<const NoDestructor>();
    assert(p);
  }
}
