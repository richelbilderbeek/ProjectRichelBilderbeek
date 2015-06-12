#ifndef RIBI_DNA_R_H
#define RIBI_DNA_R_H

#include <memory>
#include <vector>

namespace ribi { struct DnaSequence; }

///DNA stuff using R scripts
struct DnaR
{
  DnaR();

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


#endif // RIBI_DNA_R_H
