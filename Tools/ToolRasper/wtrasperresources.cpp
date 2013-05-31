#include "wtrasperresources.h"

#include <cassert>
#include <iostream>

#include <QFile>

namespace ToolRasper {

WtResources::WtResources()
{
  #ifndef NDEBUG
  Test();
  #endif
}

void WtResources::Create(const std::string& filename)
{
  if (!QFile::exists(filename.c_str()))
  {
    const QString q = QString(":/images/") + QString(filename.c_str());
    QFile file(q);
    file.copy(filename.c_str());
    file.close();
  }
  if (!QFile::exists(filename.c_str()))
  {
    std::cerr << "Warning: '" << filename << "' not found\n";
  }
  assert(QFile::exists(filename.c_str()));

}

const std::string WtResources::GetImageBackgroundFilename() const
{
  const std::string s = "RichelbilderbeekNlBackground.png";
  Create(s);
  return s;
}

const std::string WtResources::GetImageGpioFilename() const
{
  const std::string s = "ToolRasperGpioLayout.png";
  Create(s);
  return s;
}

const std::string WtResources::GetImageRaspberryPiDiagonallyFilename() const
{
  const std::string s = "ToolRasperRaspberryPiDiagonally.jpg";
  Create(s);
  return s;
}

const std::string WtResources::GetImageRaspberryPiTopFilename() const
{
  const std::string s = "ToolRasperRaspberryPiTop.jpg";
  Create(s);
  return s;
}

void WtResources::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  WtResources().GetImageBackgroundFilename();
  WtResources().GetImageGpioFilename();
  WtResources().GetImageRaspberryPiDiagonallyFilename();
  WtResources().GetImageRaspberryPiTopFilename();
}

} //namespace ToolRasper
