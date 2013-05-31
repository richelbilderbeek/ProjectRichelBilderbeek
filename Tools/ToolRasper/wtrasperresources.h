#ifndef WTRASPERRESOURCES_H
#define WTRASPERRESOURCES_H

#include <string>

namespace ToolRasper {

struct WtResources
{
  WtResources();
  const std::string GetImageBackgroundAttribute() const { return "(C) Richel Bilderbeek"; }
  const std::string GetImageBackgroundFilename() const;
  const std::string GetImageBackgroundSource() const { return "http://www.richelbilderbeek.nl"; }

  const std::string GetImageGpioAttribute() const { return "(C) Matt / raspberrypi-spy.co.uk"; }
  const std::string GetImageGpioFilename() const;
  const std::string GetImageGpioSource() const { return "http://www.raspberrypi-spy.co.uk/2012/06/simple-guide-to-the-rpi-gpio-header-and-pins"; }

  const std::string GetImageRaspberryPiTopAttribute() const { return "(C) Maiakaat / Wikimedia Commons / CC-BY-SA-2.0 / Front of Raspberry Pi"; }
  const std::string GetImageRaspberryPiTopFilename() const;
  const std::string GetImageRaspberryPiTopSource() const { return "http://commons.wikimedia.org/wiki/File:Front_of_Raspberry_Pi.jpg"; }

  const std::string GetImageRaspberryPiDiagonallyAttribute() const { return "(C) cowjuice / Wikimedia Commons / CC-BY-SA-3.0 / Raspberry Pi Photo"; }
  const std::string GetImageRaspberryPiDiagonallyFilename() const;
  const std::string GetImageRaspberryPiDiagonallySource() const { return "http://commons.wikimedia.org/wiki/File:Raspberry_Pi_Photo.jpg"; }

  private:

  static void Create(const std::string& filename);

  static void Test();
};

} //namespace ToolRasper

#endif // WTRASPERRESOURCES_H
