//---------------------------------------------------------------------------

#ifndef UnitTapButtonH
#define UnitTapButtonH
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include "UnitController.h"
#include "UnitMemFunCommand.h"
//---------------------------------------------------------------------------
export template <class T>
struct TapButton : public Controller
{
  typedef void (T::* MemFunPtr)();

  TapButton(T * const target, const MemFunPtr command)
  : mCommand(target,command)
  {

  }


  void Tap()
  {
    mCommand.Execute();
  }

  private:

  const MemFunCommand<T> mCommand;

  //TapButton can only be deleted by boost::shared_ptr
  virtual ~TapButton() {}
  friend boost::checked_delete(TapButton *);

};
//---------------------------------------------------------------------------



#endif
