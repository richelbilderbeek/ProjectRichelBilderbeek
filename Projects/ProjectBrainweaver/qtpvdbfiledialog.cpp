#include "qtpvdbfiledialog.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>

#include "pvdbfile.h"

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

const boost::shared_ptr<QFileDialog> QtFileDialog::GetSaveFileDialog()
{
  boost::shared_ptr<QFileDialog> d(new QFileDialog);

  //enum ViewMode { Detail, List };
  d->setViewMode(QFileDialog::Detail);

  //enum FileMode { AnyFile, ExistingFile, Directory, ExistingFiles, DirectoryOnly };
  d->setFileMode(QFileDialog::AnyFile);

  //enum AcceptMode { AcceptOpen, AcceptSave };
  d->setAcceptDrops(QFileDialog::AcceptSave);

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

} //~namespace pvdb
