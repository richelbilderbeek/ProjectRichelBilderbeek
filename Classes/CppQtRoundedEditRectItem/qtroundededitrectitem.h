//---------------------------------------------------------------------------
/*
QtRoundedEditRectItem, editable rectangular-shaped QGraphicsItem
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
//From http://www.richelbilderbeek.nl/QtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#ifndef QTROUNDEDEDITRECTITEM_H
#define QTROUNDEDEDITRECTITEM_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#include <QFont>
#include "qtroundedrectitem.h"
#include "qtroundededitrectitempadding.h"
#pragma GCC diagnostic pop

namespace ribi {

///A QtRoundedRectTextItem displaying multiple lines of text
///For a single line of text, use QtRoundedEditRectItem
class QtRoundedEditRectItem : public QtRoundedRectItem
{
  //Q_OBJECT //Cannot make this a QObject???

  public:
  typedef QtRoundedRectItem Base;
  typedef QtRoundedEditRectItemPadding Padding;


  explicit QtRoundedEditRectItem(
    const std::vector<std::string>& text = { "..." },
    const Padding& padding = Padding(),
    const QFont& font = QFont("monospace",9),
    QGraphicsItem* parent = 0
  );

  virtual ~QtRoundedEditRectItem() noexcept;

  ///Get the font by which the text is drawn
  const QFont& GetFont() const noexcept;

  const Padding& GetPadding() const noexcept { return m_padding; }

  ///Obtain the text on the item
  const std::vector<std::string>& GetText() const noexcept;

  const QPen& GetTextPen() const noexcept { return m_text_pen; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the font by which the text is drawn
  void SetFont(const QFont& font) noexcept;

  ///Set the padding between text and rectangle
  void SetPadding(const Padding& padding) noexcept;

  ///Set the text displayed
  void SetText(const std::vector<std::string>& text) noexcept;

  ///Set the pen by which the text is drawn
  void SetTextPen(const QPen& pen) noexcept;

  ///Called when the user wants to edit the text
  //boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_item_requests_edit;

  boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_base_changed;
  boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_font_changed;
  boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_padding_changed;
  boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_text_changed;
  boost::signals2::signal<void(QtRoundedEditRectItem*)> m_signal_text_pen_changed;

protected:
  virtual void keyPressEvent(QKeyEvent* event) noexcept;
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept;

private:

  ///The font by which the text is drawn
  QFont m_font;

  ///Set the padding between text and rectangle
  Padding m_padding;

  ///The text displayed
  std::vector<std::string> m_text;

  ///Set the padding around text, so the text will be centered
  static const Padding m_text_padding;

  ///The pen by which the text is drawn
  QPen m_text_pen;

  ///Obtain the unpadded text rectangle for a single line
  static QRectF GetTextRect(const std::string& s, const QFont& font) noexcept;

  ///Obtain the unpadded text rectangle for the whole text
  ///Note: even this rectangle is enlarged by a pixel in both dimensions, so the text will be drawn in full
  static QRectF GetTextRect(const std::vector<std::string>& text, const QFont& font) noexcept;

  ///Obtain the padded text rectangle for a single line
  static QRectF GetPaddedTextRect(const std::string& s, const QFont& font) noexcept;

  ///Called whenever a base class item is changed
  void OnBaseChanged(QtRoundedRectItem * const) noexcept;

  void SetInnerHeight(const double) = delete;
  void SetInnerWidth(const double) = delete;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

//std::ostream& operator<<(std::ostream& os, const QtRoundedEditRectItem&) noexcept;

} //~namespace ribi

#endif // QTROUNDEDEDITRECTITEM_H
