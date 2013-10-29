#include "createqtprojectzipfilemaindialog.h"
#include "qtcreatorprofilezipscript.h"

ribi::CreateQtProjectZipFileMainDialog::CreateQtProjectZipFileMainDialog(
  const std::string& source_folder)
  : m_script(QtCreatorProFileZipScript::CreateScript(source_folder))
{

}
