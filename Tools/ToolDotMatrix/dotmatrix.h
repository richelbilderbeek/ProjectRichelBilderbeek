#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include <string>
#include <vector>
#include <boost/array.hpp>

namespace Extctrls { struct TImage; }

//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
void DotMatrix(
  Extctrls::TImage * const image,
  const int x_co,
  const int y_co,
  const char c);

//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
void DotMatrix(
  Extctrls::TImage * const image,
  const int x_co,
  const int y_co,
  const std::string& s);

//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
void DotMatrix(
  Extctrls::TImage * const image,
  const int x_co,
  const int y_co,
  const std::vector<std::string>& v);

//Dot-matrix characters are
//size 5 (width) x 7 (height) pixels, excluding empty spacer pixels
//size 6 (width) x 8 (height) pixels, including empty spacer pixels
const boost::array<boost::array<int,5> ,7> GetMatrix(const char c);

//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  Extctrls::TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);

//Set a line of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  Extctrls::TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);

//Set a square of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  Extctrls::TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);


#endif


#endif // DOTMATRIX_H
