#ifndef QTPVDBFILEDIALOG_H
#define QTPVDBFILEDIALOG_H

#include <boost/shared_ptr.hpp>

struct QFileDialog;

namespace ribi {

namespace pvdb {

struct QtFileDialog
{
  enum class FileType { cmp, pdf };
  ///Create a QFileDialog to open Brainweaver files with
  static const boost::shared_ptr<QFileDialog> GetOpenFileDialog();

  ///Create a QFileDialog to save Brainweaver files with
  static const boost::shared_ptr<QFileDialog> GetSaveFileDialog(const FileType type);
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBFILEDIALOG_H
