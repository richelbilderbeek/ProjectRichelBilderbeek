//---------------------------------------------------------------------------

#ifndef UnitCreateMachinesH
#define UnitCreateMachinesH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
struct TFormMachine;
struct TFormSimStagecraftMain;
//---------------------------------------------------------------------------
std::vector<boost::shared_ptr<TFormMachine> > CreateMachines(
  TFormSimStagecraftMain * const formParent,
  const int level);
//---------------------------------------------------------------------------
#endif
