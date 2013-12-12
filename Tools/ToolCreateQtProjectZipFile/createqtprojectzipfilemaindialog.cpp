#include "createqtprojectzipfilemaindialog.h"

#include <cassert>

#include "qtcreatorprofilezipscript.h"
#include "trace.h"

ribi::CreateQtProjectZipFileMainDialog::CreateQtProjectZipFileMainDialog(
  const std::string& source_folder)
  : m_script(QtCreatorProFileZipScript::CreateScript(source_folder))
{
  #ifndef NDEBUG
  Test();
  #endif

}

#ifndef NDEBUG
void ribi::CreateQtProjectZipFileMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CreateQtProjectZipFileMainDialog::Test");
  TRACE("Finished ribi::CreateQtProjectZipFileMainDialog::Test successfully");
}
#endif
