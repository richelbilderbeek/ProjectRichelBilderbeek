//---------------------------------------------------------------------------

#ifndef UnitKeylistH
#define UnitKeylistH
//---------------------------------------------------------------------------
#include <set>
#include <vector>
#include "UnitEnums.h"
//---------------------------------------------------------------------------
struct KeyList
{
  void AddKey(const EnumKey& key);
  void RemoveKey(const EnumKey& key);
  std::vector<EnumKey> GetKeys() const;
  private:
  std::set<EnumKey> mSet;
};
#endif
