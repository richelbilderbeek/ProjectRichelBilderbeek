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
#ifndef UnitFormOptionsH
#define UnitFormOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#include <set>
#include "UnitQuestionType.h"
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageVerbEasy;
        TImageList *ImageList;
        TImage *ImageNounMedium;
        TImage *ImageSentenceMedium;
        TImage *ImageVerbMedium;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TImage *ImageNounEasy;
        TImage *ImageSentenceEasy;
        TImage *ImageNounHard;
        TImage *ImageSentenceHard;
        TImage *ImageVerbHard;
        TImage *Image10;
        TImage *ImageDone;
        TLabel *LabelDone;
        void __fastcall ImageDoneClick(TObject *Sender);
        void __fastcall ImageVerbEasyClick(TObject *Sender);
        void __fastcall ImageVerbMediumClick(TObject *Sender);
        void __fastcall ImageVerbHardClick(TObject *Sender);
        void __fastcall ImageNounEasyClick(TObject *Sender);
        void __fastcall ImageNounMediumClick(TObject *Sender);
        void __fastcall ImageNounHardClick(TObject *Sender);
        void __fastcall ImageSentenceEasyClick(TObject *Sender);
        void __fastcall ImageSentenceMediumClick(TObject *Sender);
        void __fastcall ImageSentenceHardClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TFormOptions(TComponent* Owner);
        static std::set<QuestionType> mOptions;
        static void SetDefaultOptions();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
