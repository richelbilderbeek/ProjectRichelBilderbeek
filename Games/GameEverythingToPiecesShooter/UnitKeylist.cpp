//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitKeylist.h"
//---------------------------------------------------------------------------
#include <Assert.hpp>
//---------------------------------------------------------------------------
void KeyList::AddKey(const EnumKey& key)
{
  mSet.insert(key);
}
//---------------------------------------------------------------------------
void KeyList::RemoveKey(const EnumKey& key)
{
  #ifndef NDEBUG
  const int oldSize = mSet.size();
  const bool isInSet = mSet.count(key);
  #endif

  mSet.erase(key);

  #ifndef NDEBUG
  const int newSize = mSet.size();
  Assert( isInSet == false || (isInSet == true && newSize == oldSize - 1));
  #endif

}
//---------------------------------------------------------------------------
std::vector<EnumKey> KeyList::GetKeys() const
{
  std::vector<EnumKey> v;
  //Get all the keys
  for (std::set<EnumKey>::const_iterator i = mSet.begin(); i != mSet.end(); ++i)
  {
    v.push_back(*i);
  }

  /*
  //The keys up and down must be remembered only once
  if (mSet.count(keyUp)   != 0) mSet.erase(keyUp);
  if (mSet.count(keyDown) != 0) mSet.erase(keyDown);
   */
  return v;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
