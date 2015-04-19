#ifndef FASTAFILE_H
#define FASTAFILE_H

#include <string>
#include <vector>

#include "dnasequence.h"

namespace ribi { struct DnaSequence; }

///Creates a Fasta file
struct FastaFile
{
  explicit FastaFile(const std::string& filename) : FastaFile(ReadSequencesFromFile(filename)) {}
  explicit FastaFile(const std::vector<ribi::DnaSequence>& sequences);

  const std::vector<ribi::DnaSequence>& GetSequences() const noexcept { return m_sequences; }
  private:
  const std::vector<ribi::DnaSequence> m_sequences;


  std::vector<ribi::DnaSequence> ReadSequencesFromFile(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif



  friend std::ostream& operator<<(std::ostream& os, const FastaFile file);
};

std::ostream& operator<<(std::ostream& os, const FastaFile file);

#endif // FASTAFILE_H
