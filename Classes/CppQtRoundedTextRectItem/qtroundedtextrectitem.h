//---------------------------------------------------------------------------
/*
QtRoundedTextRectItem, rectangular-shaped multi-line QGraphicsItem
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTROUNDEDTEXTRECTITEM_H
#define QTROUNDEDTEXTRECTITEM_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>

#include <QFont>

#include "qtroundedrectitem.h"
#pragma GCC diagnostic pop

namespace ribi {

///A QtRoundedTextItem displays a single line of text
///For multiple lines of text, use QtRoundedEditRectItem
struct QtRoundedTextRectItem : public QtRoundedRectItem
{
  struct Padding
  {
    Padding(const double any_top = 0.0, const double any_right = 0.0, const double any_bottom = 0.0, const double any_left = 0.0)
      : bottom(any_bottom), left(any_left), right(any_right), top(any_top) {}
    double bottom;
    double left;
    double right;
    double top;
  };

  QtRoundedTextRectItem(
    const std::string& text = "...",
    const Padding& padding = Padding(),
    const QFont& font = QFont("monospace",9),
    QGraphicsItem* parent = 0);

  ///ABC must have public virtual destructor
  virtual ~QtRoundedTextRectItem() noexcept {}

  ///Get the font by which the text is drawn
  const QFont& GetFont() const noexcept { return m_font; }

  ///Get the text
  const std::string& GetText() const noexcept { return m_text; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the font by which the text is drawn
  void SetFont(const QFont& font) noexcept;

  ///Set the padding between text and rectangle
  void SetPadding(const Padding& padding) noexcept;

  ///Set the text displayed
  void SetText(const std::string& text) noexcept;

  ///Set the pen by which the text is drawn
  void SetTextPen(const QPen& pen) noexcept;

protected:
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
  virtual void keyPressEvent(QKeyEvent* event);

private:
  ///The font by which the text is drawn
  QFont m_font;

  ///Set the padding between text and rectangle
  Padding m_padding;

  ///The text displayed
  std::string m_text;

  ///The pen by which the text is drawn
  QPen m_text_pen;

  ///Set the padding around text, so the text will be centered
  static const Padding m_text_padding;

  ///Obtain the padded text rectangle
  const QRectF GetPaddedTextRect() const;

  ///Obtain the unpadded text rectangle
  ///Note: even this rectangle is enlarged by a pixel in both dimensions, so the text will be drawn in full
  const QRectF GetTextRect() const;

};

} //~namespace ribi

#endif // QTROUNDEDTEXTRECTITEM_H
