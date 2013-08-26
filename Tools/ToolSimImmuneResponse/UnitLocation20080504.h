//---------------------------------------------------------------------------

#ifndef UnitLocation20080504H
#define UnitLocation20080504H
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitSprite.h"
#include "UnitEnum.h"
#include "UnitSimState.h"
//---------------------------------------------------------------------------
struct Location
{
  virtual void RespondToSimState() = 0;
  virtual const EnumLocation GetLocation() const = 0;
  virtual void ChangeAllSprites();

  void MoveAllSprites();

  const std::vector<boost::shared_ptr<Sprite> >& GetSprites() const { return mSprites; }
  boost::shared_ptr<Sprite>& GetSprite(const std::size_t i);
  const boost::shared_ptr<Sprite>& GetSprite(const std::size_t i) const;
  const std::vector<boost::shared_ptr<Sprite> > GetSpritesNear(
    boost::shared_ptr<Sprite>& sprite) const;

  void AddSprite(const boost::shared_ptr<Sprite>& s);
  const bool CanGrabSprite(const int x, const int y) const;
  const boost::shared_ptr<Sprite> GrabSprite(const int x, const int y);
  const bool IsPresent(const EnumCellType cellType) const;

  void RemoveEmigrants(
    std::vector<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& emigrants);
  void AddMigrants(
    std::vector<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& immigrants);

  const int Count(const EnumCellType cellType) const;

  void ReplaceAll(
    const EnumCellType replaceWhat,
    const EnumCellType replaceWith);
  void ReplaceOne(
    const EnumCellType replaceWhat,
    const EnumCellType replaceWith
    );
  void RemoveOne(const EnumCellType cellType);

  void UpdateSimState(SimState& state) const;

  private:
  std::vector<boost::shared_ptr<Sprite> > mSprites;

  struct SpriteMover : public std::unary_function<Sprite,void>
  {
    void operator() (boost::shared_ptr<Sprite>& s) const;
  };

  struct SpriteChanger : public std::unary_function<Sprite,void>
  {
    void operator() (boost::shared_ptr<Sprite>& s) const;
  };

  struct SpriteNear : public std::unary_function<Sprite,void>
  {
    SpriteNear(const boost::shared_ptr<Sprite>& sprite);
    const bool operator() (const boost::shared_ptr<Sprite>& sprite) const;
    const boost::shared_ptr<Sprite>& mSprite;
  };

  struct CellTypeFinder : public std::unary_function<Sprite,bool>
  {
    CellTypeFinder(const EnumCellType cellType);
    const bool operator() (const boost::shared_ptr<Sprite>& s) const;
    const EnumCellType mCellType;
  };
};
//---------------------------------------------------------------------------
struct BloodStream : public Location
{
  BloodStream();
  const EnumLocation GetLocation() const { return bloodStream; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------
struct BoneMarrow : public Location
{
  const EnumLocation GetLocation() const { return boneMarrow; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------
struct CellTissue : public Location
{
  CellTissue();
  const EnumLocation GetLocation() const { return cellTissue; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------
struct LymphNode : public Location
{
  const EnumLocation GetLocation() const { return lymphNode; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------




#endif
