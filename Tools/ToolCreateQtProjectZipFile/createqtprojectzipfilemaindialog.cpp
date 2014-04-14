#include "createqtprojectzipfilemaindialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/find.hpp>

#include "qtcreatorprofilezipscript.h"
#include "trace.h"
#pragma GCC diagnostic pop

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
  CreateQtProjectZipFileMainDialog d("../../Tools/ToolCreateQtProjectZipFile");
  const std::string n = "mkdir Projects/Tools/ToolCreateQtProjectZipFile/../..";
  const std::string s = d.GetScript();
  const auto p = boost::algorithm::find(s,n);
  assert(p.first == p.second);
  assert(1==2);
  TRACE("Finished ribi::CreateQtProjectZipFileMainDialog::Test successfully");
}
#endif
