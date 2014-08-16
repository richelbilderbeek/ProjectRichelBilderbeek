//---------------------------------------------------------------------------
/*
  GaborFilter, performs Gabor filter operations on images
  Copyright (C) 2010  Richel Bilderbeek

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
#ifndef UnitFormMainH
#define UnitFormMainH
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
#include <cassert>
#include <algorithm>
#include <numeric>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBoxOriginal;
        TScrollBox *ScrollBoxResult;
        TImage *ImageSource;
        TImage *ImageTarget;
        TButton *ButtonLoad;
        TButton *ButtonSaveResult;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TPageControl *PageControl;
        TTabSheet *TabSheetOriginal;
        TTabSheet *TabSheetFilter;
        TTabSheet *TabSheetResult;
        TPanel *PanelOriginal;
        TPanel *PanelResult;
        TPanel *PanelFilter;
        TTabSheet *TabSheetAbout;
        TPopupMenu *PopupMenuFilter;
        TMenuItem *ItemAddCol;
        TMenuItem *ItemAddRow;
        TMenuItem *N1;
        TMenuItem *ItemRemoveCol;
        TMenuItem *ItemRemoveRow;
        TRichEdit *RichEditLicence;
        TPanel *PanelAboutTop;
        TPanel *PanelAbout1;
        TPanel *PanelAbout2;
        TPanel *PanelAbout3;
        TPanel *PanelAbout6;
        TPanel *PanelAbout5;
        TPanel *PanelVersion;
        TImage *ImageRichel;
        TButton *ButtonDo;
        TTrackBar *TrackBarAngle;
        TLabel *LabelAngle;
        TTrackBar *TrackBarWavelength;
        TLabel *LabelWavelength;
        TTrackBar *TrackBarSize;
        TLabel *LabelSize;
        TImage *ImageFilter;
        TPanel *PanelTopRight;
        TLabel *LabelSigma;
        TButton *ButtonWhatsNew;
        TPanel *Panel1;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall ButtonSaveResultClick(TObject *Sender);
        void __fastcall ButtonDoClick(
          TObject *Sender);
        void __fastcall OnAnyTrackBarChange(TObject *Sender);
        void __fastcall ButtonWhatsNewClick(TObject *Sender);
private:	// User declarations
  std::vector<std::vector<double> > mFilter;
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
const std::vector<std::vector<double> > CreateGaborFilter(
  const int sz,
  const double angle,
  const double wavelength,
  const double sigma);
//---------------------------------------------------------------------------
const std::vector<std::vector<double> > DoFilterOperation(
  const std::vector<std::vector<double> >& source, //y-x-ordered
  const std::vector<std::vector<double> >& filter); //y-x-ordered
//---------------------------------------------------------------------------
//Creates a 2D-std::vector (y-x-ordered) from a TImage
const std::vector<std::vector<int> > ImageToVector(const TImage * const image);
//---------------------------------------------------------------------------
const double GetFilterOperationPixel(
  const std::vector<std::vector<double> >& source, //y-x-ordered
  const int sourceX,
  const int sourceY,
  const std::vector<std::vector<double> >& filter); //y-x-ordered
//---------------------------------------------------------------------------
const std::pair<double,double> GetMinMax(const std::vector<std::vector<double> >& v);
//---------------------------------------------------------------------------
//Obtains the maximum element of a 2D container
//From http://www.richelbilderbeek.nl/CppMaxElement.htm
template <class Container>
const Container::value_type::value_type MaxElement(const Container& v)
{
  assert(v.empty() == false && "Container must have a size");

  //Obtain an initial lowest value
  Container::value_type::value_type maxValue 
    = *(std::max_element(v[0].begin(),v[0].end()));

  //Set the iterators
  const Container::const_iterator rowEnd = v.end();
  Container::const_iterator row = v.begin();
  ++row; //Move to the next position, as index 0 is already read from

  for ( ; row != rowEnd; ++row) //row is already initialized
  {
    const Container::value_type::value_type localMaxVal
      = *(std::max_element(row->begin(),row->end()));
    if (localMaxVal > maxValue) maxValue = localMaxVal;
  }
  return maxValue;
}
//---------------------------------------------------------------------------
//Obtains the minimum element of a 2D container
//From http://www.richelbilderbeek.nl/CppMinElement.htm
template <class Container>
const Container::value_type::value_type MinElement(const Container& v)
{
  assert(v.empty() == false && "Container must have a size");

  //Obtain an initial lowest value
  Container::value_type::value_type minValue 
    = *(std::min_element(v[0].begin(),v[0].end()));

  //Set the iterators
  const Container::const_iterator rowEnd = v.end();
  Container::const_iterator row = v.begin();
  ++row; //Move to the next position, as index 0 is already read from

  for ( ; row != rowEnd; ++row) //row is already initialized
  {
    const Container::value_type::value_type localMinVal
      = *(std::min_element(row->begin(),row->end()));
    if (localMinVal < minValue) minValue = localMinVal;
  }
  return minValue;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRescale.htm
const double Rescale(
  const double value,
  const double oldMin,
  const double oldMax,
  const double newMin,
  const double newMax);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRescale.htm
const std::vector<std::vector<double> > Rescale(
  std::vector<std::vector<double> > v,
  const double newMin,
  const double newMax);
//---------------------------------------------------------------------------
template <class Source, class Target>
const std::vector<std::vector<Target> > Convert(
  const std::vector<std::vector<Source> >& v)
{
  const int maxy = static_cast<int>(v.size());
  assert(maxy>0);
  const int maxx = static_cast<int>(v[0].size());
  std::vector<std::vector<Target> > t(maxy,std::vector<Target>(maxx));
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      t[y][x] = static_cast<Target>(v[y][x]);
    }
  }
  return t;
}
//---------------------------------------------------------------------------
//Fills a TImage from a 2D-std::vector (y-x-ordered)
void VectorToImage(const std::vector<std::vector<int> >& v, const TImage * const image);
//---------------------------------------------------------------------------
//From http://richelbilderbeek.nl/CppToolGaborFilter.htm
const double CalculateSigma(const int sz);
//---------------------------------------------------------------------------

#endif
