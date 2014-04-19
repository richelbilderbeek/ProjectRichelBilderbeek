#include "wtrasperresources.h"

#include <cassert>
#include <iostream>

#include <QFile>

ribi::ToolRasper::WtResources::WtResources()
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::ToolRasper::WtResources::Create(const std::string& filename) noexcept
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

std::string ribi::ToolRasper::WtResources::GetImageBackgroundFilename() const noexcept
{
  const std::string s = "RichelbilderbeekNlBackground.png";
  Create(s);
  return s;
}

std::string ribi::ToolRasper::WtResources::GetImageGpioFilename() const noexcept
{
  const std::string s = "ToolRasperGpioLayout.png";
  Create(s);
  return s;
}

std::string ribi::ToolRasper::WtResources::GetImageRaspberryPiDiagonallyFilename() const noexcept
{
  const std::string s = "ToolRasperRaspberryPiDiagonally.jpg";
  Create(s);
  return s;
}

std::string ribi::ToolRasper::WtResources::GetImageRaspberryPiTopFilename() const noexcept
{
  const std::string s = "ToolRasperRaspberryPiTop.jpg";
  Create(s);
  return s;
}

void ribi::ToolRasper::WtResources::Test()
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
