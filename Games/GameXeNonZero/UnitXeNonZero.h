//---------------------------------------------------------------------------

#ifndef UnitXeNonZeroH
#define UnitXeNonZeroH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "UnitArea.h"
struct Sprite;
struct SpritePlayer;
//---------------------------------------------------------------------------
struct XeNonZero
{
  typedef boost::shared_ptr<Sprite> SpritePtr;
  typedef std::vector<boost::shared_ptr<Sprite> > SpriteContainer;

  typedef SpriteContainer::iterator Iterator;
  typedef SpriteContainer::const_iterator ConstIterator;

  XeNonZero();
  void AskUserInputAndProcess();

  const bool IsGameOver() const;
  void DrawSprites();

  const Area& GetArea() const { return mArea; }
  const int GetAreaHeight() const;
  const int GetAreaWidth() const;

  private:


  void MoveSprites();
  void LetSpritesInteract();

  Area mArea;
  SpriteContainer mSprites;
  boost::shared_ptr<SpritePlayer> mSpritePlayer;
};


std::ostream& operator<<(std::ostream& os, const XeNonZero& s);

const std::string AskUserInput();

struct SpriteMover : public std::unary_function<void,Sprite>
{
  void operator()(boost::shared_ptr<Sprite>& s) const;
};

struct SpriteDrawer : public std::unary_function<void,Sprite>
{
  SpriteDrawer(Area& area) : mArea(area) {}
  void operator()(boost::shared_ptr<Sprite>& s) const;
  Area& mArea;
};

struct SpriteIsDead : public std::unary_function<bool,Sprite>
{
  bool operator()(boost::shared_ptr<Sprite>& s) const;
};

struct SpriteShoot : public std::unary_function<void,Sprite>
{
  SpriteShoot(XeNonZero::SpriteContainer& tempSprites) : mTempSprites(tempSprites) {}
  void operator()(boost::shared_ptr<Sprite>& s) const;
  XeNonZero::SpriteContainer& mTempSprites;
};

#endif
