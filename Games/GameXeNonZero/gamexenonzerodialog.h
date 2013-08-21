#ifndef GAMEXENONZERODIALOG_H
#define GAMEXENONZERODIALOG_H

#include <iosfwd>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "gamexenonzerofwd.h"
#include "gamexenonzeroarea.h"

namespace xnz {


struct Dialog
{
  enum class Input { up, right, down, left, space, shoot };

  typedef boost::shared_ptr<Sprite> SpritePtr;
  typedef std::vector<boost::shared_ptr<Sprite> > SpriteContainer;
  typedef SpriteContainer::iterator Iterator;
  typedef SpriteContainer::const_iterator ConstIterator;

  Dialog();

  const boost::shared_ptr<const Area> ProcessInput(const Input input);
  bool IsGameOver() const;

  private:

  void DrawSprites();

  const boost::shared_ptr<const xnz::Area> GetArea() const { return mArea; }

  void MoveSprites();
  void LetSpritesInteract();

  const boost::shared_ptr<xnz::Area> mArea;

  SpriteContainer mSprites;
  boost::shared_ptr<SpritePlayer> mSpritePlayer;

  friend std::ostream& operator<<(std::ostream& os, const Dialog& s);
};


std::ostream& operator<<(std::ostream& os, const Dialog& s);

//const std::string AskUserInput();

struct SpriteMover : public std::unary_function<void,Sprite>
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

struct SpriteIsDead : public std::unary_function<bool,Sprite>
{
  bool operator()(boost::shared_ptr<Sprite>& s) const;
};

struct SpriteShoot : public std::unary_function<void,Sprite>
{
  SpriteShoot(Dialog::SpriteContainer& tempSprites) : mTempSprites(tempSprites) {}
  void operator()(boost::shared_ptr<Sprite>& s) const;
  Dialog::SpriteContainer& mTempSprites;
};

} //~namespace xnz

#endif
