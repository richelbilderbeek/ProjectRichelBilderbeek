//---------------------------------------------------------------------------

#ifndef UnitCommandH
#define UnitCommandH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppCommandDesignPattern.htm
//---------------------------------------------------------------------------
template <class T>
struct Command
{
  typedef void (*FunctionPointer)(T& target);

  Command(boost::shared_ptr<T> target, const FunctionPointer functionPointer)
    : mTarget(target), mFunction(functionPointer) { }
  void Execute() { mFunction( *( mTarget.get() ) ); }
  private:
  boost::shared_ptr<T> mTarget;
  FunctionPointer mFunction;
};
//---------------------------------------------------------------------------
#endif
