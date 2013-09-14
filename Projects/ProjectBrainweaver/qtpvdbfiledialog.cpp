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

  const std::string namefile = std::string("Brainweaver concept map (*.")
    + pvdb::File::GetFilenameExtension() + std::string(")");

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
      namefile = std::string("Brainweaver concept map (*.")
      + pvdb::File::GetFilenameExtension() + std::string(")");
    break;
    case FileType::pdf:
      namefile = std::string("Portable document format (*.pdf)");
    break;
  }

  d->setNameFilter(namefile.c_str());

  return d;
}

} //~namespace pvdb

} //~namespace ribi
