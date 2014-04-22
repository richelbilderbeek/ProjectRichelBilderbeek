//---------------------------------------------------------------------------
/*
 *  Das Wahre Schlagerfest. A simple game.
 *  Copyright (C) 2003  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
#ifndef UnitThreeDotsChasingH
#define UnitThreeDotsChasingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <AppEvnts.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#define NDEBUG
#include <vector>
#include <assert>
#include <math>
#include <time>
//---------------------------------------------------------------------------
class TFormThreeDotsChasing : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TApplicationEvents *ApplicationEvents1;
  void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
  void __fastcall FormClick(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormThreeDotsChasing(TComponent* Owner);
  //int count;
  std::vector< std::vector<unsigned char> > distance;

  struct Point
  {
    short x;
    short y;
    char dx;
    char dy;
  };
  short abs(const short& i) { return (i<0 ? -i : i); }
  std::vector< Point > points;
  void resetPoints();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormThreeDotsChasing *FormThreeDotsChasing;
//---------------------------------------------------------------------------
#endif
