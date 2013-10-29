#ifndef CREATEQTPROJECTZIPFILEMAINDIALOG_H
#define CREATEQTPROJECTZIPFILEMAINDIALOG_H

#include <string>

namespace ribi {

struct CreateQtProjectZipFileMainDialog
{
  CreateQtProjectZipFileMainDialog(const std::string& source_folder);

  const std::string GetScript() const noexcept { return m_script; }

  private:
  const std::string m_script;
};

} //~namespace ribi

#endif // CREATEQTPROJECTZIPFILEMAINDIALOG_H
