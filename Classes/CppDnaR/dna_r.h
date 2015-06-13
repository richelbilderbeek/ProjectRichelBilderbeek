#ifndef RIBI_DNA_R_H
#define RIBI_DNA_R_H

#include <memory>
#include <string>
#include <vector>

namespace ribi { struct DnaSequence; }

namespace ribi {

///DNA stuff using R scripts
struct DnaR
{
  DnaR();

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  void PlotSequences(
    const std::vector<ribi::DnaSequence>& sequences,
    const std::string& filename
  ) const;

  private:

  void PlotSequencesRinside(
    const std::vector<ribi::DnaSequence>& sequences,
    const std::string& filename
  ) const;

  void PlotSequencesRscript(
    const std::vector<ribi::DnaSequence>& sequences,
    const std::string& filename
  ) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_DNA_R_H
