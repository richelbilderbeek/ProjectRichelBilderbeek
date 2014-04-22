#include <memory>

struct MyClass
{
  //interface

  private:
  ~MyClass() {}
  friend struct std::default_delete<MyClass>;
};

int main()
{
  //MyClass c; //OK: should not compile

  //Posted question to
  //  http://stackoverflow.com/questions/22091559/c11-alternative-to-boostchecked-delete
  //const std::shared_ptr<MyClass> d {
  //  std::make_shared<MyClass>()
  //}; //Should compile

  //Posted question to
  //  http://stackoverflow.com/questions/22091559/c11-alternative-to-boostchecked-delete
  const std::shared_ptr<MyClass> d(
    new MyClass,std::default_delete<MyClass>()
  ); //Does compile
}

