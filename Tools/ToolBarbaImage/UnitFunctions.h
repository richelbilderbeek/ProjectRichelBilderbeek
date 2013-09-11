//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
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
#ifndef UnitFunctionsH
#define UnitFunctionsH
//---------------------------------------------------------------------------
#include <vector>
namespace Extctrls { class TImage; }

namespace bikkel
{

  //From http://www.richelbilderbeek.nl/CppAddColoredNoise.htm
  void AddColoredNoise(
    const Extctrls::TImage * const source,
    const int max_rand,
    Extctrls::TImage * const target);

  void Bleach(
    const TImage * const imageOriginal,
    const int fraction_of_256,
    TImage * const imageResult);

  //From http://www.richelbilderbeek.nl/CppBleach.htm
  void Bleach(
    const TImage * const imageOriginal,
    const double fraction,
    TImage * const imageResult);

  void Darken(
    const TImage * const imageOriginal,
    const int fraction_of_256,
    TImage * const imageResult);

  //From http://www.richelbilderbeek.nl/CppDarken.htm
  void Darken(
    const TImage * const imageOriginal,
    const double fraction,
    TImage * const imageResult);

  //From http://www.richelbilderbeek.nl/CppDoHistogramEqualization.htm
  void DoHistogramEqualization(
    const Extctrls::TImage * const source,
    Extctrls::TImage * const target);

  //From http://www.richelbilderbeek.nl/CppExtractBlue.htm
  void ExtractBlue(
    const Extctrls::TImage * const source,
    Extctrls::TImage * const target);

  //From http://www.richelbilderbeek.nl/CppExtractGreen.htm
  void ExtractGreen(
    const Extctrls::TImage * const source,
    Extctrls::TImage * const target);

  //From http://www.richelbilderbeek.nl/CppExtractRed.htm
  void ExtractRed(
    const Extctrls::TImage * const source,
    Extctrls::TImage * const target);


  //From htpp://www.richelbilderbeek.nl/CppGetCumulativeHistogram.htm
  export template <class T> const std::vector<T>
  GetCumulativeHistogram(const std::vector<T>& histogram);

  //From htpp://www.richelbilderbeek.nl/CppGetImageHistogram.htm
  const std::vector<int> GetImageHistogram(const Extctrls::TImage * const image);

  //From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
  void ThresholdFilterColor(
    const TImage * const imageOriginal,
    const int threshold,
    TImage * const imageResult);

  //From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
  void ThresholdFilterNoColor(
    const TImage * const imageOriginal,
    const int threshold,
    TImage * const imageResult);

  //From http://www.richelbilderbeek.nl/CppEnhanceContrast.htm
  void EnhanceContrast(const TImage * const image);

  //From http://www.richelbilderbeek.nl/CppConvertToGrey.htm
  void ConvertToGrey(const TImage * const source, TImage * const target);

  //From http://www.richelbilderbeek.nl/CppGetAverageGreyness.htm
  const double GetAverageGreyness(const TImage * const image);


}
//---------------------------------------------------------------------------
#endif
