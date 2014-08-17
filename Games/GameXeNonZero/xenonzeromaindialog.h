#ifndef GAMEXENONZERODIALOG_H
#define GAMEXENONZERODIALOG_H

#include <iosfwd>
#include <vector>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "xenonzerofwd.h"
#include "xenonzeroarea.h"
#include "xenonzerokey.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace xnz {

struct Dialog
{

  typedef boost::shared_ptr<Sprite> SpritePtr;
  typedef std::vector<boost::shared_ptr<Sprite> > SpriteContainer;
  typedef SpriteContainer::iterator Iterator;
  typedef SpriteContainer::const_iterator ConstIterator;

  Dialog();

  const boost::shared_ptr<const Area> OnKeyPress(const Key input);
  bool IsGameOver() const;

  const boost::shared_ptr<TextCanvas> GetTextCanvas() const noexcept;

  private:

  void DrawSprites();

  const boost::shared_ptr<const xnz::Area> GetArea() const { return mArea; }

  void MoveSprites();
  void LetSpritesInteract();

  boost::shared_ptr<Area> mArea;

  boost::shared_ptr<SpritePlayer> mSpritePlayer;
  SpriteContainer mSprites;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Dialog& s);
};


std::ostream& operator<<(std::ostream& os, const Dialog& s);

//const std::string AskUserInput();

struct SpriteMover
{
  void operator()(boost::shared_ptr<Sprite>& s) const;
};

/*
struct SpriteDrawer : public std::unary_function<void,Sprite>
{
  SpriteDrawer(Area& area) : mArea(area) {}
  void operator()(boost::shared_ptr<Sprite>& s) const;
  Area& mArea;
};
*/

struct SpriteIsDead
{
  bool operator()(boost::shared_ptr<Sprite>& s) const;
};

struct SpriteShoot
{
  SpriteShoot(Dialog::SpriteContainer& tempSprites) : mTempSprites(tempSprites) {}
  void operator()(boost::shared_ptr<Sprite>& s) const;
  Dialog::SpriteContainer& mTempSprites;
};

} //~namespace xnz

} //~namespace ribi

#endif
