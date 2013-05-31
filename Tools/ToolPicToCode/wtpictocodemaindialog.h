//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#ifndef WTPICTOCODEDIALOG_H
#define WTPICTOCODEDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
#include "pictocodemaindialog.h"
//---------------------------------------------------------------------------
struct QImage;
//---------------------------------------------------------------------------
namespace Wt
{
  struct WButtonGroup;
  struct WFileUpload;
  struct WTextArea;
  struct WImage;
}
//---------------------------------------------------------------------------
struct WtPicToCodeWidget;
//---------------------------------------------------------------------------
struct WtPicToCodeMainDialog : public Wt::WContainerWidget
{
  WtPicToCodeMainDialog();
  private:
  Wt::WPushButton * const m_button_convert;
  Wt::WFileUpload * const m_fileupload;
  Wt::WButtonGroup * m_group;
  Wt::WTextArea * const m_text;
  boost::scoped_ptr<Wt::WImage> m_image;
  void on_upload_done();
  void on_convert();


  const PicToCodeMainDialog::YxImage QtImageToImage(const QImage& qt_image) const;
  //const PicToCodeMainDialog::YxImage ImageToImage(const Wt::WImage& wt_image) const;

};
//---------------------------------------------------------------------------
#endif // WTPICTOCODEDIALOG_H
