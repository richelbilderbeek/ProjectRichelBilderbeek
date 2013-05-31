//---------------------------------------------------------------------------
/*
QtRubiksClockWidget, Wt widget for displaying the RubiksClock class
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtRubiksClockWidget.htm
//---------------------------------------------------------------------------
#ifndef QTRUBIKSCLOCKWIDGET_H
#define QTRUBIKSCLOCKWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include <QWidget>

#include "rubiksclock.h" //Required by MOC
#include "rubiksclockwidget.h" //Required by MOC

namespace Wt { struct WMouseEventEvent; }
struct QPainter;
struct RubiksClock;

///QtRubiksClockWidget displays a RubiksClock
class QtRubiksClockWidget : public QWidget
{
  Q_OBJECT

public:
  ///A QtRubiksClockWidget is created by its toggle state and its color
  QtRubiksClockWidget(
    const bool toggled = false,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Obtain a read-only pointer to the RubiksClockWidget
  const RubiksClockWidget * GetWidget() const { return m_widget.get(); }

  ///Obtain a read-and-write pointer to the RubiksClockWidget
  RubiksClockWidget * GetWidget() { return m_widget.get(); }

  ///Obtain the QtRubiksClockWidget its version
  static const std::string GetVersion();

  ///Obtain the QtRubiksClockWidget its version history
  static const std::vector<std::string> GetVersionHistory();

  ///\brief
  ///Draw the RubiksClock
  ///
  ///Because a Rubik's Clock has two sides, the parameter
  ///front_size determines whether to draw the front side or the back side
  static void DrawRubiksClock(
    QPainter& painter,
    const int x, const int y,
    const int width, const int height,
    const RubiksClock * const clock,
    const bool front_size);

  ///Draw the RubiksClock
  static void DrawRubiksClock(
    QPainter& painter,
    const RubiksClockWidget * const widget);

  protected:
  ///Paint the QtRubiksClockWidget
  void paintEvent(QPaintEvent *);
  //void paintEvent(Wt::WPaintDevice *paintDevice);
  void mousePressEvent(QMouseEvent *);

  private:
  ///The RubiksClockWidget
  boost::scoped_ptr<RubiksClockWidget> m_widget;

  ///Do not let this be called by the client
  void resize(const int width, const int height);

  ///Repaint the QtRubiksClockWidget
  void DoRepaint();

  ///Respond to the widget resizing
  void OnResize();
};


/*

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "UnitRubiksClock.h"

class TFormRubiksClockMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageClockFront;
        TImage *ImageClockBack;
        TPanel *Panel1;
        TButton *ButtonAbout;
        TButton *ButtonShuffle;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ImageClockFrontMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ImageClockBackMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall ButtonShuffleClick(TObject *Sender);
private:	// User declarations
  RubiksClock mClock;
  void DrawScreen();
public:		// User declarations
        __fastcall TFormRubiksClockMain(TComponent* Owner);
};

extern PACKAGE TFormRubiksClockMain *FormRubiksClockMain;

void DrawRubiksClock(
  const RubiksClockTimes& times,
  const RubiksClockPegs& pegs,
  const TColor colorCasing,
  const TColor colorClock,
  TImage * const image);

void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );

*/

#endif // QTRUBIKSCLOCKWIDGET_H
