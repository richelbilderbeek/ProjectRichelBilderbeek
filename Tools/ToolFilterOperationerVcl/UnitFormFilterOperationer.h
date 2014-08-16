//---------------------------------------------------------------------------
/*
  FilterOperationer, performs filter operations on images
  Copyright (C) 2008  Richel Bilderbeek

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
#ifndef UnitFormFilterOperationerH
#define UnitFormFilterOperationerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
//---------------------------------------------------------------------------
class TFormFilterOperationer : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBoxOriginal;
        TScrollBox *ScrollBoxResult;
        TImage *ImageSource;
        TImage *ImageTarget;
        TStringGrid *StringGridFilter;
        TButton *ButtonDo;
        TButton *ButtonLoad;
        TButton *ButtonSaveResult;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TButton *ButtonEnhance;
        TPageControl *PageControl;
        TTabSheet *TabSheetOriginal;
        TTabSheet *TabSheetFilter;
        TTabSheet *TabSheetResult;
        TTabSheet *TabSheetEnhancedResult;
        TPanel *PanelOriginal;
        TPanel *PanelResult;
        TPanel *PanelFilter;
        TPanel *PanelEnhanced;
        TButton *ButtonSaveEnhanced;
        TTabSheet *TabSheetAbout;
        TPopupMenu *PopupMenuFilter;
        TMenuItem *ItemAddCol;
        TMenuItem *ItemAddRow;
        TMenuItem *N1;
        TMenuItem *ItemRemoveCol;
        TMenuItem *ItemRemoveRow;
        TScrollBox *ScrollBoxEnhanced;
        TImage *ImageEnhanced;
        TRichEdit *RichEditLicence;
        TPanel *PanelAboutTop;
        TPanel *PanelAbout1;
        TPanel *PanelAbout2;
        TPanel *PanelAbout3;
        TPanel *PanelAbout6;
        TPanel *PanelAbout5;
        TPanel *PanelAbout4;
        TImage *ImageRichel;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall ButtonDoClick(TObject *Sender);
        void __fastcall ButtonSaveResultClick(TObject *Sender);
        void __fastcall ButtonEnhanceClick(TObject *Sender);
        void __fastcall ItemAddColClick(TObject *Sender);
        void __fastcall ItemAddRowClick(TObject *Sender);
        void __fastcall ItemRemoveColClick(TObject *Sender);
        void __fastcall ItemRemoveRowClick(TObject *Sender);
        void __fastcall ButtonSaveEnhancedClick(TObject *Sender);
        void __fastcall PanelAbout3Click(TObject *Sender);
        void __fastcall OnStringGridFilterChange(TObject *Sender);
        void __fastcall OnStringGridFilterChange2(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TFormFilterOperationer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFilterOperationer *FormFilterOperationer;
//---------------------------------------------------------------------------
//VCL dependent
export template <class T>
const std::vector<std::vector<T> > StringGridToVector(const TStringGrid * const stringGrid);

export template <class T>
const bool CanStringGridToVector(const TStringGrid * const stringGrid);

//VCL dependent
void DoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGrid,
  TImage * const target);

const bool CanDoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGridFilter,
  TImage * const imageTarget);

void EnhanceContrast(const TImage * const image);

const double GetAverageGreyness(const TImage * const image);


//Creates a 2D-std::vector (y-x-ordered) from a TImage
const std::vector<std::vector<int> > ImageToVector(const TImage * const image);

//Fills a TImage from a 2D-std::vector (y-x-ordered)
void VectorToImage(const std::vector<std::vector<int> >& v, const TImage * const image);

void Trace(const std::vector<std::string>& v);

void Trace(const std::string& s);

export template <class T>
void Trace(const std::vector<std::vector<T> >& v);

void Trace(const std::vector<std::vector<int> >& v);


//VCL independent
/*
const std::vector<std::vector<int> >
  DoFilterOperation(
    const std::vector<std::vector<int> >& imageSource,
    const std::vector<std::vector<double> >& filter);
*/

const double GetFilterOperationPixel(
  const std::vector<std::vector<int> >& source, //y-x-ordered
  const int sourceX,
  const int sourceY,
  const std::vector<std::vector<double> >& filter); //y-x-ordered


const std::vector<std::vector<int> > DoFilterOperation(
  const std::vector<std::vector<int> >& source, //y-x-ordered
  const std::vector<std::vector<double> >& filter); //y-x-ordered

const std::pair<double,double> GetFilterRange(const std::vector<std::vector<double> >& filter);

//const std::vector<std::vector<int> > GetRescaledImage(
//  const std::vector<std::vector<int> >& source);

//const std::vector<std::vector<int> > GetRescaledImage(
//  const std::vector<std::vector<int> >& source,
//  const std::vector<std::vector<double> >& filter);



//export template <class T>
//const double GetAverage(const std::vector<std::vector<T> >& v);

//From http://www.richelbilderbeek.nl/CppDoHistogramEqualization.htm
void DoHistogramEqualization(const TImage * const source, TImage * const target);

//From htpp://www.richelbilderbeek.nl/CppGetCumulativeHistogram.htm
template <class T> const std::vector<T> GetCumulativeHistogram(const std::vector<T>& histogram);

//From htpp://www.richelbilderbeek.nl/CppGetImageHistogram.htm
const std::vector<int> GetImageHistogram(const TImage * const image);

//From http://www.richelbilderbeek.nl/CppCanCast.htm
template <class TargetType> const bool CanCast(const std::string& from);

//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
template <typename TargetType>
const TargetType LexicalCast(const std::string& s);

//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
export template <>
const int LexicalCast<int>(const std::string& s);

//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
export  template <>
const double LexicalCast<double>(const std::string& s);


#endif
