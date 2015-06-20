#ifndef RIBI_HISTOGRAM_R_H
#define RIBI_HISTOGRAM_R_H

#include <memory>
#include <string>
#include <vector>

#include "RInside.h"

struct RInside;

namespace ribi {

struct HistogramR
{
  enum class GraphicsFormat { png, svg };

  HistogramR();

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Plot histogram to file
  void ToHistogram(
    const std::vector<double>& v,
    const std::string& filename,
    const GraphicsFormat graphics_format
  ) const;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_HISTOGRAM_R_H
