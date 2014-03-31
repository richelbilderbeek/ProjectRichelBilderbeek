//---------------------------------------------------------------------------
/*
 *  Frysk Leare Lieder. A program to train the Frysian language.
 *  Copyright (C) 2007  Richel Bilderbeek
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
#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <memory>
#include "UnitQuestionGenerator.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TEdit *ControlAnswer;
        TImage *ImageLetterSirconflex;
        TStaticText *ControlQuestion;
        TPanel *PanelBottom;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *LabelCorrect;
        TLabel *LabelIncorrect;
        TLabel *LabelAbout;
        TLabel *LabelQuit;
        TLabel *Label3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        void __fastcall LabeledEdit1Enter(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ControlAnswerKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall LabelQuitClick(TObject *Sender);
        void __fastcall LabelAboutClick(TObject *Sender);
        void __fastcall LabelOptionsClick(TObject *Sender);
        void __fastcall ImageLetterSirconflexMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
        std::auto_ptr<QuestionGenerator> mQuestionGenerator;
        void DrawScreen();
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
