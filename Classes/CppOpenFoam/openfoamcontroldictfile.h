#ifndef OPENFOAMCONTROLDICTFILE_H
#define OPENFOAMCONTROLDICTFILE_H

#include <iosfwd>
#include <vector>
#include "openfoamfwd.h"
#include "openfoamheader.h"

namespace ribi {
namespace foam {

///Reads and writes an OpenFOAM thermophysicalProperties file
struct ControlDictFile
{
  explicit ControlDictFile(
    const Header header = GetDefaultHeader()
  );

  static Header GetDefaultHeader() noexcept;
  const Header& GetHeader() const noexcept { return m_header; }

  void SetAdjustTimeStep(const bool adjust_time_step) noexcept { m_adjust_time_step = adjust_time_step; }
  void SetApplication(const std::string& application) noexcept { m_application = application; }
  void SetDeltaT(const double delta_t) noexcept { m_delta_t = delta_t; }
  void SetEndTime(const double end_time) noexcept { m_end_time = end_time; }
  void SetPurgeWrite(const int purge_write) noexcept { m_purge_write = purge_write; }
  void SetRunTimeModifiable(const bool run_time_modifiable) { m_run_time_modifiable = run_time_modifiable; }
  void SetStartFrom(const std::string& start_from) noexcept { m_start_from = start_from; }
  void SetStartTime(const double start_time) noexcept { m_start_time = start_time; }
  void SetStopAt(const std::string& stop_at) noexcept { m_stop_at = stop_at; }
  void SetTimeFormat(const std::string& time_format) noexcept { m_time_format = time_format; }
  void SetTimePrecision(const int time_precision) noexcept { m_time_precision = time_precision; }
  void SetWriteCompression(const std::string& write_compression) noexcept { m_write_compression = write_compression; }
  void SetWriteControl(const std::string& write_control) noexcept { m_write_control = write_control; }
  void SetWriteFormat(const std::string& write_format) noexcept { m_write_format = write_format; }
  void SetWriteInterval(const double write_interval) noexcept { m_write_interval = write_interval; }
  void SetWritePrecision(const int write_precision) noexcept { m_write_precision = write_precision; }
  private:

  bool m_adjust_time_step;
  std::string m_application;
  double m_delta_t;
  double m_end_time;

  ///The OpenFOAM header
  Header m_header;

  int m_purge_write;
  std::string m_start_from;
  double m_start_time;
  std::string m_stop_at;
  std::string m_time_format;
  int m_time_precision;
  bool m_run_time_modifiable;
  std::string m_write_compression;
  std::string m_write_control;
  std::string m_write_format;
  double m_write_interval;
  int m_write_precision;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const ControlDictFile& f) noexcept;
};

std::ostream& operator<<(std::ostream& os, const ControlDictFile& f) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMCONTROLDICTFILE_H
