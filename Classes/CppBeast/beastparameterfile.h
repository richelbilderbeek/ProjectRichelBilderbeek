#ifndef BEASTPARAMETERFILE_H
#define BEASTPARAMETERFILE_H

#include <string>
#include <vector>

namespace ribi { struct DnaSequence; }

///Creates a BEAST XML parameter file
struct BeastParameterFile
{
  enum class TreePrior { birth_death, coalescent_constant_population };

  /// alignment_base_filename: if the alignment was made
  ///   from e.g. 'MyData.fas', alignment_base_filename must be 'MyData'
  BeastParameterFile(
    const std::vector<ribi::DnaSequence>& sequences,
    const std::string& alignment_base_filename,
    const int mcmc_chainlength,
    const TreePrior tree_prior
  );

  const std::vector<ribi::DnaSequence>& GetSequences() const noexcept { return m_sequences; }
  int GetMcmcChainlengths() const noexcept { return m_mcmc_chainlength; }
  TreePrior GetTreePrior() const noexcept { return m_tree_prior; }

  ///Convert an alignment
  std::vector<std::string> ToBirthDeathXml() const noexcept;

  private:
  const std::string m_alignment_base_filename;
  const int m_mcmc_chainlength;
  const std::vector<ribi::DnaSequence> m_sequences;
  const TreePrior m_tree_prior;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const BeastParameterFile file);

#endif // BEASTPARAMETERFILE_H
