//---------------------------------------------------------------------------
/*
TestPylos, tool to test Pylos class
Copyright (C) 2010-2015 Richel Bilderbeek

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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/array.hpp>
#include <QPixmap>
#pragma GCC diagnostic pop

namespace ribi {
namespace pylos {

const boost::array<int,6> GetBlackWhiteColors();
const boost::array<int,6> GetDefaultColors();
const boost::array<int,6> GetRedBlueColors();

struct QtSprites
{
  enum class Type  { player1, player2, player1_select, player2_select, player1_remove, player2_remove, board_bottom, board_hole };

  QtSprites(
    const int board_width = 64,
    const int board_height = 64,
    const boost::array<int,6>& colors = GetDefaultColors())
    : QtSprites(board_width,board_height,colors,board_width/4,board_height/4,64) {}

  ///Get returns the pixmap of a certain sprite
  const QPixmap& Get(const Type sprite) const;

  int GetBoardWidth() const { return m_board_width; }
  int GetBoardHeight() const { return m_board_height; }

  ///Obtain the color scheme
  const boost::array<int,6>& GetColorScheme() const { return m_colors; }

  int GetMarbleWidth() const { return m_board_width / 4; }
  int GetMarbleHeight() const { return m_board_height / 4; }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///SetBoardSize resizes the sprites to the
  ///required sizes
  //void SetBoardSize(const int board_width, const int board_height);

  ///SetColorScheme sets the color scheme of the Sprites.
  ///This redraws all the sprites.
  //void SetColorScheme(const boost::array<int,6> colors);

  private:
  ///The implementation of the public constructor
  QtSprites(
    const int board_width,
    const int board_height,
    const boost::array<int,6>& colors,
    const int square_width,
    const int square_height,
    const int greyness_hole
    );

  const int m_board_height;
  const int m_board_width;
  const boost::array<int,6> m_colors;
  const QPixmap m_sprite_board_bottom;
  const QPixmap m_sprite_board_hole;
  const QPixmap m_sprite_player1;
  const QPixmap m_sprite_player1_remove;
  const QPixmap m_sprite_player1_select;
  const QPixmap m_sprite_player2;
  const QPixmap m_sprite_player2_remove;
  const QPixmap m_sprite_player2_select;
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

} //~namespace pylos
} //~namespace ribi

#endif // QTPYLOSSPRITES_H
