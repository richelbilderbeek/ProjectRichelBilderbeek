//---------------------------------------------------------------------------

#ifndef UnitMemFunCommandH
#define UnitMemFunCommandH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppCommandDesignPattern.htm
//---------------------------------------------------------------------------
template <class T>
struct MemFunCommand
{
  typedef void (T::* MemFunPtr)();

  MemFunCommand(T * const target, const MemFunPtr memFun)
    : mTarget(target), mFunction(memFun) { }
  void Execute() { (mTarget->*mFunction)(); }
  private:
  T * mTarget;
  MemFunPtr mFunction;
};
//---------------------------------------------------------------------------
#endif
