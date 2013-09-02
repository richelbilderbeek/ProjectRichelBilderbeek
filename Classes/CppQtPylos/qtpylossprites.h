//---------------------------------------------------------------------------
/*
TestPylos, tool to test Pylos class
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTPYLOSSPRITES_H
#define QTPYLOSSPRITES_H

#include <boost/array.hpp>
#include <QPixmap>

//#include "pylosgame.h"

namespace Pylos {

const boost::array<int,6> GetBlackWhiteColors();
const boost::array<int,6> GetDefaultColors();
const boost::array<int,6> GetRedBlueColors();

struct QtSprites
{
  enum class Type  { player1, player2, player1_select, player2_select, player1_remove, player2_remove, board_bottom, board_hole };

  QtSprites(
    const int board_width = 64,
    const int board_height = 64,
    const boost::array<int,6>& colors = GetDefaultColors());

  ///Get returns the pixmap of a certain sprite
  const QPixmap& Get(const Type sprite) const;

  int GetBoardWidth() const { return m_board_width; }
  int GetBoardHeight() const { return m_board_height; }
  int GetMarbleWidth() const { return m_board_width / 4; }
  int GetMarbleHeight() const { return m_board_height / 4; }

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///SetBoardSize resizes the sprites to the
  ///required sizes
  void SetBoardSize(const int board_width, const int board_height);

  ///SetColorScheme sets the color scheme of the Sprites.
  ///This redraws all the sprites.
  void SetColorScheme(const boost::array<int,6> colors);

  private:
  int m_board_width;
  int m_board_height;
  boost::array<int,6> m_colors;
  void GenerateSprites();

  QPixmap m_sprite_player1;
  QPixmap m_sprite_player2;
  QPixmap m_sprite_player1_select;
  QPixmap m_sprite_player2_select;
  QPixmap m_sprite_player1_remove;
  QPixmap m_sprite_player2_remove;
  QPixmap m_sprite_board_bottom;
  QPixmap m_sprite_board_hole;
};

QPixmap DrawBoardBottom(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b);

///From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
QPixmap DrawGlobe(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b);

///From http://www.richelbilderbeek.nl/CppDrawInvertedGlobe.htm
QPixmap DrawInvertedGlobe(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b);

QPixmap DrawRemover(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b);

QPixmap DrawSelector(
  const int width,
  const int height,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b);

//From http://www.richelbilderbeek.nl/CppPaint.htm
void Paint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a = 255); //Opaque

} //~namespace Pylos

#endif // QTPYLOSSPRITES_H
