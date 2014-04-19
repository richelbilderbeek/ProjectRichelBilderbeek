#include <set>
#include <functional>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct MyClass
{
  MyClass(const int x) : m_x(x) {}
  const int m_x;

  friend class boost::detail::sp_ms_deleter<      MyClass>;
  friend class boost::detail::sp_ms_deleter<const MyClass>;
  //friend void boost::checked_delete<>(      MyClass* x);
  //friend void boost::checked_delete<>(const MyClass* x);
};

int main()
{
  std::vector<boost::shared_ptr<MyClass>> v {
    boost::make_shared<MyClass>(0),
    boost::make_shared<MyClass>(1),
    boost::make_shared<MyClass>(2),
    boost::make_shared<MyClass>(3),
    boost::make_shared<MyClass>(4),
    boost::make_shared<MyClass>(5)
  };


  typedef std::set<
    boost::shared_ptr<MyClass>,
    std::function<bool(boost::shared_ptr<const MyClass>,boost::shared_ptr<const MyClass>)>
  > MySet;

  //This code below will throw a std::bad_function_call
  try
  {
    MySet s;

    std::copy_if(
      v.begin(),v.end(),
      std::inserter(s,s.begin()),
      [](const boost::shared_ptr<MyClass> i)
      {
        assert(i);
        const bool do_copy = i->m_x % 2;
        return do_copy;
      }
    );
  }
  catch (std::bad_function_call&)
  {
    //Ok, should fail
  }

  //This code below will not throw a std::bad_function_call
  MySet s(
    [](const boost::shared_ptr<const MyClass>& lhs,const boost::shared_ptr<const MyClass>& rhs)
    {
      return lhs->m_x < rhs->m_x;
    }
  );

  assert(s.size() == 0);

  std::copy_if(
    v.begin(),v.end(),
    std::inserter(s,s.begin()),
    [](const boost::shared_ptr<MyClass> i)
    {
      assert(i);
      const bool do_copy = i->m_x % 2;
      return do_copy;
    }
  );

  assert(s.size() == 3);
}

