#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gamexenonzerodialog.h"

#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>

#include <cassert>

#include "gamexenonzerosprite.h"
#pragma GCC diagnostic pop

ribi::xnz::Dialog::Dialog()
  : mArea(new Area(78,23)),
    mSpritePlayer(new SpritePlayer(78/2-2,23-1-4)),
    mSprites{}
{
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemyMedium(35, 1)));
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemySmall(20, 6)));
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemySmall(30, 8)));
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemySmall(40,10)));
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemySmall(50,12)));
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemySmall(60,14)));
  mSprites.push_back( boost::shared_ptr<Sprite>(new SpriteEnemySmall(70,16)));

  DrawSprites();
}

bool ribi::xnz::Dialog::IsGameOver() const
{
  return (mSpritePlayer->GetHealth() <= 0);
}

/*
void xnzribi::xnz::Dialog::AskUserInputAndProcess()
{
  const std::string userInput = AskUserInput();

  if      (userInput == "a") { mSpritePlayer->Move(-1, 0); }
  else if (userInput == "d") { mSpritePlayer->Move( 1, 0); }
  else if (userInput == "w") { mSpritePlayer->Move( 0,-1); }
  else if (userInput == "s") { mSpritePlayer->Move( 0, 1); }
  else if (userInput == "x")
  {
    SpriteContainer tempSprites;
    mSpritePlayer->Shoot(tempSprites);
    std::copy(tempSprites.begin(),tempSprites.end(),std::back_inserter(mSprites));
  }
  else if (userInput == "q")
  {
    //Kill player to be game over
    mSpritePlayer->ChangeHealth( -mSpritePlayer->GetHealth() - 1);
  }

  MoveSprites();


  LetSpritesInteract();
  DrawSprites();

}
*/

const boost::shared_ptr<const ribi::xnz::Area>
  ribi::xnz::Dialog::ProcessInput(const ribi::xnz::Dialog::Input input)
{
  switch (input)
  {
    case Input::up:
      mSpritePlayer->Move( 0,-1);
      break;
    case Input::right:
      mSpritePlayer->Move( 1, 0);
      break;
    case Input::down:
      mSpritePlayer->Move( 0,-1);
      break;
    case Input::left:
      mSpritePlayer->Move(-1, 0);
      break;
    case Input::shoot:
    {
      SpriteContainer tempSprites;
      mSpritePlayer->Shoot(tempSprites);
      std::copy(tempSprites.begin(),tempSprites.end(),std::back_inserter(mSprites));
    }
    case Input::space:
    break;
  }
  MoveSprites();
  LetSpritesInteract();
  DrawSprites();
  return GetArea();
}

void ribi::xnz::Dialog::MoveSprites()
{
  std::for_each(mSprites.begin(),mSprites.end(),SpriteMover());
}

void ribi::xnz::Dialog::LetSpritesInteract()
{
  //Let player interact with all non-player sprites
  {
    const Iterator j = mSprites.end();
    for(Iterator i = mSprites.begin(); i!=j; ++i)
    {
      if (IsCollision(mSpritePlayer,*i)==true)
      {
        mSpritePlayer->ChangeHealth(-1);
        (*i)->ChangeHealth(-1);
      }

    }
  }

  //Let all non-player sprites interact with all non-player sprites
  {
    const Iterator end = mSprites.end();
    for(Iterator i = mSprites.begin(); i!=end; ++i)
    {
      for(Iterator j = i + 1 ; j!=end; ++j)
      {
        assert(i!=j);
        if (IsCollision(*i,*j)==true)
        {
          (*i)->ChangeHealth(-1);
          (*j)->ChangeHealth(-1);
        }
      }
    }
  }

  //Check for health of sprites and remove them
  {
    //Erase-remove from Meyers, Effective STL, Item 32
    mSprites.erase(
      std::remove_if( mSprites.begin(),mSprites.end(), SpriteIsDead()),mSprites.end());
  }

  //Let the enemies shoot
  {
    SpriteContainer tempSprites;
    std::for_each(mSprites.begin(),mSprites.end(), SpriteShoot(tempSprites));
    std::copy(tempSprites.begin(),tempSprites.end(),std::back_inserter(mSprites));
  }

}

void ribi::xnz::Dialog::DrawSprites()
{
  mArea->DrawEdge();

  mArea->Draw(
    mSpritePlayer->GetX(),
    mSpritePlayer->GetY(),
    mSpritePlayer->GetGraphic());

  for(auto s: mSprites)
  {
    mArea->Draw(s->GetX(), s->GetY(), s->GetGraphic());
  }

  mArea->DrawLife(
    static_cast<double>(mSpritePlayer->GetHealth())
    / static_cast<double>(mSpritePlayer->GetMaxHealth() ) );
}

/*
void SpriteDrawer::operator()(boost::shared_ptr<Sprite>& s) const
{
  mArea->Draw(s->GetX(), s->GetY(), s->GetGraphic());
}
*/

/*
const std::string AskUserInput()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}
*/

std::ostream& ribi::xnz::operator<<(std::ostream& os, const Dialog& s)
{
  os << s.GetArea();
  return os;
}

void ribi::xnz::SpriteMover::operator()(boost::shared_ptr<Sprite>& s) const
{
  s->Move();
}

bool ribi::xnz::SpriteIsDead::operator()(boost::shared_ptr<Sprite>& s) const
{
  return s->IsDead();
}

void ribi::xnz::SpriteShoot::operator()(boost::shared_ptr<Sprite>& s) const
{
  s->Shoot(mTempSprites);
}
