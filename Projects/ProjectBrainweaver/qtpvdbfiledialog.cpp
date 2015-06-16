//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbfiledialog.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>

#include "pvdbfile.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace pvdb {

const boost::shared_ptr<QFileDialog> QtFileDialog::GetOpenFileDialog()
{
  boost::shared_ptr<QFileDialog> d(new QFileDialog);

  //enum ViewMode { Detail, List };
  d->setViewMode(QFileDialog::Detail);

  //enum FileMode { AnyFile, ExistingFile, Directory, ExistingFiles, DirectoryOnly };
  d->setFileMode(QFileDialog::ExistingFile);

  //enum AcceptMode { AcceptOpen, AcceptSave };
  d->setAcceptDrops(QFileDialog::AcceptOpen);

  //enum Option { ShowDirsOnly, DontResolveSymlinks, DontConfirmOverwrite, DontUseSheet, DontUseNativeDialog, ReadOnly, HideNameFilterDetails }
  d->setOptions(QFileDialog::ReadOnly);

  const std::string namefile = "Brainweaver concept map (*."
    + pvdb::File::GetFilenameExtension() + ")";

  d->setNameFilter(namefile.c_str());

  //Put the dialog in the screen center
  //const QRect screen = QApplication::desktop()->screenGeometry();
  //d->move( screen.center() - d->rect().center() );

  return d;
}

const boost::shared_ptr<QFileDialog> QtFileDialog::GetSaveFileDialog(const FileType type)
{
  boost::shared_ptr<QFileDialog> d(new QFileDialog);

  //enum ViewMode { Detail, List };
  d->setViewMode(QFileDialog::Detail);

  //enum FileMode { AnyFile, ExistingFile, Directory, ExistingFiles, DirectoryOnly };
  d->setFileMode(QFileDialog::AnyFile);

  //enum AcceptMode { AcceptOpen, AcceptSave };
  d->setAcceptDrops(QFileDialog::AcceptSave);

  //enum Option { ShowDirsOnly, DontResolveSymlinks, DontConfirmOverwrite, DontUseSheet, DontUseNativeDialog, ReadOnly, HideNameFilterDetails }
  d->setOptions( QFileDialog::DontUseNativeDialog ); //Workaround for https://bugreports.qt-project.org/browse/QTBUG-29248

  std::string namefile;
  switch (type)
  {
    case FileType::cmp:
      namefile = "Brainweaver concept map (*."
      + pvdb::File::GetFilenameExtension() + ")";
    break;
    case FileType::pdf:
      namefile = "Portable document format (*.pdf)";
    break;
  }

  d->setNameFilter(namefile.c_str());

  return d;
}

} //~namespace pvdb

} //~namespace ribi
