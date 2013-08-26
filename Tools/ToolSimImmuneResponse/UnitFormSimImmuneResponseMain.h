//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
  Copyright (C) 2008  Richèl Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitFormSimImmuneResponseMainH
#define UnitFormSimImmuneResponseMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include <boost/scoped_ptr.hpp>
#include "UnitSimImmuneResponse.h"
struct TFormSimImmuneResponseFeedback;
struct TFormSimImmuneResponseInfo;
struct TFormSimImmuneResponseLegend;
struct TFormSimImmuneResponseOptions;
struct Sprite;
//---------------------------------------------------------------------------
class TFormSimImmuneResponseMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TImage *ImageBoneMarrow;
        TImage *ImageBloodStream;
        TImage *ImageCellTissue;
        TImage *ImageLymphNode;
        TTimer *TimerSprites;
        TImage *ImageBloodStreamBackground;
        TImage *ImageBoneMarrowBackground;
        TImage *ImageCellTissueBackground;
        TImage *ImageLymphNodeBackground;
        TTimer *TimerFeedback;
        TLabel *Label1;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall TimerSpritesTimer(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall TimerFeedbackTimer(TObject *Sender);
private:	// User declarations
  boost::scoped_ptr<TFormSimImmuneResponseFeedback> mFormFeedback;
  boost::scoped_ptr<TFormSimImmuneResponseInfo> mFormInfo;
  boost::scoped_ptr<TFormSimImmuneResponseLegend> mFormLegend;
  boost::scoped_ptr<TFormSimImmuneResponseOptions> mFormOptions;
  boost::shared_ptr<Sprite> mSprite;
  SimImmuneResponse mSim;
  bool mMouseDown;
  bool mDraggingSomething;
  const EnumLocation GetLocation(const int x, const int y) const;
  const int mNpaneCols;
  const int mNpaneRows;
public:		// User declarations
  __fastcall TFormSimImmuneResponseMain(TComponent* Owner);
  const int GetClientWidth() const;
  const int GetClientHeight() const;
  const int GetLocationWidth() const;
  const int GetLocationHeight() const;
  const int GetSpriteWidth() const;
  const int GetSpriteHeight() const;
  const TImage * const ToImage(
    const EnumCellType t) const;
  void AddCell(const EnumCellType cellType);
  void Restart();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimImmuneResponseMain *FormSimImmuneResponseMain;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetFontHeight.htm
const int GetFontHeight(const TImage * const image);

void DrawTextCentered(TImage* const image, const std::string& s);

#endif
