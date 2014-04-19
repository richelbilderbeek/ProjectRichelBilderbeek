#ifndef WTRASPERRESOURCES_H
#define WTRASPERRESOURCES_H

#include <string>

namespace ribi {
namespace ToolRasper {

struct WtResources
{
  WtResources();
  std::string GetImageBackgroundAttribute() const noexcept { return "(C) Richel Bilderbeek"; }
  std::string GetImageBackgroundFilename() const noexcept;
  std::string GetImageBackgroundSource() const noexcept { return "http://www.richelbilderbeek.nl"; }

  std::string GetImageGpioAttribute() const noexcept { return "(C) Matt / raspberrypi-spy.co.uk"; }
  std::string GetImageGpioFilename() const noexcept;
  std::string GetImageGpioSource() const noexcept { return "http://www.raspberrypi-spy.co.uk/2012/06/simple-guide-to-the-rpi-gpio-header-and-pins"; }

  std::string GetImageRaspberryPiTopAttribute() const noexcept { return "(C) Maiakaat / Wikimedia Commons / CC-BY-SA-2.0 / Front of Raspberry Pi"; }
  std::string GetImageRaspberryPiTopFilename() const noexcept;
  std::string GetImageRaspberryPiTopSource() const noexcept { return "http://commons.wikimedia.org/wiki/File:Front_of_Raspberry_Pi.jpg"; }

  std::string GetImageRaspberryPiDiagonallyAttribute() const noexcept { return "(C) cowjuice / Wikimedia Commons / CC-BY-SA-3.0 / Raspberry Pi Photo"; }
  std::string GetImageRaspberryPiDiagonallyFilename() const noexcept;
  std::string GetImageRaspberryPiDiagonallySource() const noexcept { return "http://commons.wikimedia.org/wiki/File:Raspberry_Pi_Photo.jpg"; }

  private:

  static void Create(const std::string& filename) noexcept;

  static void Test();
};

} //~namespace ToolRasper
} //~namespace ribi

#endif // WTRASPERRESOURCES_H
