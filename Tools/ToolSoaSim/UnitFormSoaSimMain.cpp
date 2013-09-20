//---------------------------------------------------------------------------
/*
  SoaSim, a simulator of sexually transmitted diseases
  Copyright (C) 2007  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>
#include "UnitPerson.h"

#include <vcl.h>
#pragma hdrstop

#include "UnitFormSoaSimMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSoaSimMain *FormSoaSimMain;
//---------------------------------------------------------------------------
__fastcall TFormSoaSimMain::TFormSoaSimMain(TComponent* Owner)
        : TForm(Owner)
{
  DrawGlobe(ImagePersonRed   , 255,   0,   0);
  DrawGlobe(ImagePersonGreen ,   0, 255,   0);
  DrawGlobe(ImagePersonBlue  ,   0,   0, 255);
  DrawGlobe(ImagePersonCustom, 255, 255, 255);
  DrawGlobe(ImageShadow      ,  64,  64,  64);
  ImagePersonRed->Transparent = true;
  ImagePersonGreen->Transparent = true;
  ImagePersonBlue->Transparent = true;
  ImagePersonCustom->Transparent = true;
  ImageShadow->Transparent = true;

  ImageBlaLeft->Picture->Bitmap->TransparentColor = clLime;
  ImageProposeUnsafe->Picture->Bitmap->TransparentColor = clLime;
  ImageProposeSafe->Picture->Bitmap->TransparentColor = clLime;
  ImageSafeSex->Picture->Bitmap->TransparentColor = clLime;
  ImageUnsafeSex->Picture->Bitmap->TransparentColor = clLime;
  ImageBlaLeft->Transparent = true;
  ImageProposeUnsafe->Transparent = true;
  ImageProposeSafe->Transparent = true;
  //ImageSafeSex->Transparent = true;
  //ImageUnsafeSex->Transparent = true;



  OnResize(0);

  //Create persons
  {
    const int nPersons = 20;
    //First add an infected Bad Boy
    AddBadBoy(true);

    mPersons.front()->isInfected = true;

    for (int i=0; i!=nPersons-1; ++i)
    {
      switch( (std::rand() >> 4) % 3)
      {
        case 0: AddBadBoy(false); break;
        case 1: AddPartyAnimal(false); break;
        case 2: AddWiseGuy(false); break;
        default:
          assert(!"Should not get here");
          break;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimMain::FormResize(TObject *Sender)
{
  ImageBuffer->Picture->Bitmap->Width  = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;
  ImageBackground->Picture->Bitmap->Width  = ClientWidth;
  ImageBackground->Picture->Bitmap->Height = ClientHeight;
  PaintVcl(ImageBackground,255,255,255);
}
//---------------------------------------------------------------------------
void TFormSoaSimMain::DrawScreen()
{
  //Draw background on buffer
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  //Draw infected solitary persons on buffer
  {
    const std::list<boost::shared_ptr<Person > >::iterator j = mPersons.end();
    for (std::list<boost::shared_ptr<Person > >::iterator i = mPersons.begin();
      i!=j;
      ++i)
    {
      if ((*i)->isInfected == true)
      {
        ImageBuffer->Canvas->Draw( (*i)->x + 4, (*i)->y + 4, ImageShadow->Picture->Graphic );
      }
    }
  }

  //Draw infected couples
  {
    const std::list<Interaction>::iterator j = mInteractions.end();
    for (std::list<Interaction>::iterator i = mInteractions.begin();
      i!=j;
      ++i)
    {
      //Draw the couple
      if ((*i).mA->isInfected == true)
        ImageBuffer->Canvas->Draw( (*i).mA->x + 4, (*i).mA->y + 4, ImageShadow->Picture->Graphic );
      if ((*i).mB->isInfected == true)
        ImageBuffer->Canvas->Draw( (*i).mB->x + 4, (*i).mB->y + 4, ImageShadow->Picture->Graphic );
    }
  }


  //Draw solitary persons on buffer
  {
    const std::list<boost::shared_ptr<Person > >::iterator j = mPersons.end();
    for (std::list<boost::shared_ptr<Person > >::iterator i = mPersons.begin();
      i!=j;
      ++i)
    {
      ImageBuffer->Canvas->Draw( (*i)->x, (*i)->y, (*i)->image->Picture->Graphic );
    }
  }

  //Draw couples
  {
    const std::list<Interaction>::iterator j = mInteractions.end();
    for (std::list<Interaction>::iterator i = mInteractions.begin();
      i!=j;
      ++i)
    {
      //Draw the couple
      ImageBuffer->Canvas->Draw( (*i).mA->x, (*i).mA->y, (*i).mA->image->Picture->Graphic );
      ImageBuffer->Canvas->Draw( (*i).mB->x, (*i).mB->y, (*i).mB->image->Picture->Graphic );
      //Draw their interaction
      switch ((*i).mInteraction)
      {
        case Interaction::aTalksBlistens:
          ImageBuffer->Canvas->Draw( (*i).mA->x+32, (*i).mA->y-32, ImageBlaLeft->Picture->Graphic );
          break;
        case Interaction::bTalksAlistens:
          ImageBuffer->Canvas->Draw( (*i).mB->x-32, (*i).mB->y-32, ImageBlaRight->Picture->Graphic );
          break;
        case Interaction::aProposeSafe:
          ImageBuffer->Canvas->Draw( (*i).mA->x+32, (*i).mA->y-32, ImageProposeSafe->Picture->Graphic );
          break;
        case Interaction::bAgreesUnsafe:
        case Interaction::bAgreesSafe:
          ImageBuffer->Canvas->Draw( (*i).mB->x-32, (*i).mB->y-32, ImageYes->Picture->Graphic );
          break;
        case Interaction::aAndBhaveSafeSex:
          ImageBuffer->Canvas->Draw( (*i).mA->x, (*i).mA->y, ImageSafeSex->Picture->Graphic );
          break;
        case Interaction::bDisagreesSafe:
        case Interaction::bDisagreesUnsafe:
          ImageBuffer->Canvas->Draw( (*i).mB->x-32, (*i).mB->y-32, ImageNo->Picture->Graphic );
          break;
        case Interaction::aProposeUnsafe:
          ImageBuffer->Canvas->Draw( (*i).mA->x+32, (*i).mA->y-32, ImageProposeUnsafe->Picture->Graphic );
          break;
        case Interaction::aAndBhaveUnsafeSex:
          ImageBuffer->Canvas->Draw( (*i).mA->x, (*i).mA->y, ImageUnsafeSex->Picture->Graphic );
          break;
        case Interaction::aAndBleave:
          //assert(!"Should not get here");
          break;
      }
    }
  }

  //Draw buffer to screen
  Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimMain::TimerMoveTimer(TObject *Sender)
{
  const int personWidth  = ImagePersonRed->Picture->Graphic->Width;
  const int personHeight = ImagePersonRed->Picture->Graphic->Height;
  const double speed = 5.0;
  //Move everybody
  const std::list<boost::shared_ptr<Person > >::iterator j = mPersons.end();
  for (std::list<boost::shared_ptr<Person > >::iterator i = mPersons.begin();
    i!=j;
    ++i)
  {
    //Move
    (*i)->direction += (GetRandomUniform() * M_PI * 2.0 * 0.05) - (0.025 * M_PI * 2.0);
    (*i)->x += std::sin( (*i)->direction ) * speed;
    (*i)->y -= std::cos( (*i)->direction ) * speed;
    //Keep in screen
    if ((*i)->x + personWidth > ClientWidth)
    {
       (*i)->x = ClientWidth - personWidth;
       (*i)->direction += M_PI;
    }
    else if ((*i)->x < 32)
    {
       (*i)->x = 32;
       (*i)->direction -= M_PI;
    }

    if ((*i)->y + personHeight > ClientHeight)
    {
       (*i)->y = ClientHeight - personHeight;
       (*i)->direction += M_PI;
    }
    else if ((*i)->y < 32)
    {
       (*i)->y = 32;
       (*i)->direction -= M_PI;
    }
  }

  DrawScreen();
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimMain::TimerInteractionTimer(TObject *Sender)
{
  //Detect new couples
  const int personWidth  = ImagePersonRed->Picture->Graphic->Width;
  bool doRetry = true;

  while(doRetry == true)
  {
    doRetry = false;

    for (std::list<boost::shared_ptr<Person > >::iterator personA = mPersons.begin();
      personA!=mPersons.end();
      ++personA)
    {
      std::list<boost::shared_ptr<Person > >::iterator personB = personA;
      for ( ++personB;
        personB!=mPersons.end();
        ++personB)
      {
        if (GetDistance( (*personA)->x - (*personB)->x, (*personA)->y - (*personB)->y )
          < static_cast<double>(personWidth) )
        {
          //An interaction!
          mInteractions.push_back(Interaction( *personA, *personB ));
          //Remove this couple from the list
          mPersons.erase(personA);
          mPersons.erase(personB);
          //The lists are messed up, so try again
          doRetry = true;
        }
        if (doRetry == true) break;
      }
      if (doRetry == true) break;
    }
  }

  //Remove couples that ended their interaction
  {
    for (std::list<Interaction>::iterator i = mInteractions.begin();
      i!=mInteractions.end();
      ++i)
    {
      if ((*i).mInteraction == Interaction::aAndBleave)
      {
        (*i).mA->direction -= M_PI;
        (*i).mB->direction += M_PI;
        //Swap them for fun...
        mPersons.push_back( (*i).mB );
        mPersons.push_back( (*i).mA );
        std::list<Interaction>::iterator newI = i;
        --newI;
        mInteractions.erase(i);
        i = newI;
      }
    }
  }

  //Do their interactions
  {
    for (std::list<Interaction>::iterator i = mInteractions.begin();
      i!=mInteractions.end();
      ++i)
    {
      assert((*i).mInteraction != Interaction::aAndBleave);
      (*i).DoInteraction();
    }
  }
}
//---------------------------------------------------------------------------
double TFormSoaSimMain::GetPercentageInfected() const
{
  int nInfected = 0;
  int nUninfected = 0;

  //Count infected solitary persons
  {
    const std::list<boost::shared_ptr<Person > >::const_iterator j = mPersons.end();
    for (std::list<boost::shared_ptr<Person > >::const_iterator i = mPersons.begin();
      i!=j;
      ++i)
    {
      if ((*i)->isInfected == true) ++nInfected;
      else ++nUninfected;

    }
  }

  //Count infected couples
  {
    const std::list<Interaction>::const_iterator j = mInteractions.end();
    for (std::list<Interaction>::const_iterator i = mInteractions.begin();
      i!=j;
      ++i)
    {
      //Draw the couple
      if ((*i).mA->isInfected == true)
        ++nInfected;
      else
        ++nUninfected;
      if ((*i).mB->isInfected == true)
        ++nInfected;
      else
        ++nUninfected;
    }
  }

  const int sum = nInfected + nUninfected;
  if (sum==0) return 0.0;
  return 100.0 * static_cast<double>(nInfected) / static_cast<double>(sum);
}
//---------------------------------------------------------------------------
void TFormSoaSimMain::AddBadBoy(const bool isInfected)
{
  const int x = std::rand() % (ClientWidth  - 32);
  const int y = std::rand() % (ClientHeight - 32);
  mPersons.push_back(
    boost::shared_ptr<Person>(
      new Person(x,y, 0.0, 0.1, 1.0, ImagePersonRed)
      )
    );
  mPersons.back()->isInfected = isInfected;
}
//---------------------------------------------------------------------------
void TFormSoaSimMain::AddPartyAnimal(const bool isInfected)
{
  const int x = std::rand() % (ClientWidth  - 32);
  const int y = std::rand() % (ClientHeight - 32);
  mPersons.push_back(
    boost::shared_ptr<Person>(
      new Person(x,y, 0.5, 1.0, 1.0, ImagePersonGreen)
      )
    );
  mPersons.back()->isInfected = isInfected;
}
//---------------------------------------------------------------------------
void TFormSoaSimMain::AddWiseGuy(const bool isInfected)
{
  const int x = std::rand() % (ClientWidth  - 32);
  const int y = std::rand() % (ClientHeight - 32);
  mPersons.push_back(
    boost::shared_ptr<Person>(
      new Person(x,y, 1.0, 1.0, 0.1, ImagePersonBlue)
      )
    );
  mPersons.back()->isInfected = isInfected;
}
//---------------------------------------------------------------------------
void TFormSoaSimMain::AddCustomPerson(
  const double pProposeSafe,
  const double pAgreeSafe,
  const double pAgreeUnsafe,
  const bool isInfected)
{
  const int x = std::rand() % (ClientWidth  - 32);
  const int y = std::rand() % (ClientHeight - 32);
  mPersons.push_back(
    boost::shared_ptr<Person>(
      new Person(x,y, pProposeSafe, pAgreeSafe, pAgreeUnsafe, ImagePersonCustom)
      )
    );
  mPersons.back()->isInfected = isInfected;
}
//---------------------------------------------------------------------------
void TFormSoaSimMain::ClearPersons()
{
  mPersons.clear();
  mInteractions.clear();
  assert(mPersons.empty() == true);
  assert(mInteractions.empty() == true);
}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
void DrawGlobe(
  TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double midX = static_cast<double>(width ) / 2.0;
  const double midY = static_cast<double>(height) / 2.0;
  const double maxDist = std::min(midX,midY);
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double xD = static_cast<double>(x);
      const double dist = std::sqrt( ((xD - midX) * (xD - midX)) + ((yD - midY) * (yD - midY)) );
      if (dist <= maxDist)
      {
        const double relDist = dist / maxDist;
        const int r = relDist * static_cast<double>(rMax);
        const int g = relDist * static_cast<double>(gMax);
        const int b = relDist * static_cast<double>(bMax);
        assert( r >= 0);
        assert( r < 256);
        assert( g >= 0);
        assert( g < 256);
        assert( b >= 0);
        assert( b < 256);
        line[x*3+2] = (r == 0 ? 1 : r); //Never use a zero for red
        line[x*3+1] = (g == 0 ? 1 : g); //Never use a zero for green
        line[x*3+0] = (b == 0 ? 1 : b); //Never use a zero for blue
      }
      else
      {
        line[x*3+2] = 0;
        line[x*3+1] = 0;
        line[x*3+0] = 0;
      }
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      myLine[x*3+2] = red  ; //Red
      myLine[x*3+1] = green; //Green
      myLine[x*3+0] = blue ; //Blue
    }
  }
}
//---------------------------------------------------------------------------
//From www.richelbilderbeek.nl/CppGetDistance.htm
const double GetDistance(const double dX, const double dY)
{
  return (std::sqrt( (dX * dX) + (dY * dY) ) );
}
//---------------------------------------------------------------------------

















