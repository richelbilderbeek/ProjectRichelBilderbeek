#ifndef CREATEQTPROJECTZIPFILEMAINDIALOG_H
#define CREATEQTPROJECTZIPFILEMAINDIALOG_H

#include <string>

namespace ribi {

struct CreateQtProjectZipFileMainDialog
{
  CreateQtProjectZipFileMainDialog(const std::string& source_folder);

  std::string GetScript() const noexcept { return m_script; }

  private:
  const std::string m_script;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // CREATEQTPROJECTZIPFILEMAINDIALOG_H
