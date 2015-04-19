#include "fastafile.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <fstream>
#include <sstream>

#include "dnasequence.h"
#include "fileio.h"
//#include "helper.h"

FastaFile::FastaFile(
  const std::vector<ribi::DnaSequence>& sequences
) : m_sequences{sequences}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<ribi::DnaSequence> FastaFile::ReadSequencesFromFile(const std::string& filename)
{
  std::vector<std::string> text{
    ribi::fileio::FileIo().FileToVector(filename)
  };
  const int n_lines{static_cast<int>(text.size())};
  std::vector<ribi::DnaSequence> sequences;
  for (int i=0; i<n_lines; ++i)
  {
    assert(i >= 0);
    assert(i < static_cast<int>(text.size()));
    const std::string pre_description = text[i];
    if (pre_description.empty()) break;
    //Chop of the trailing '>'
    const std::string description{pre_description.substr(1,pre_description.size()-1)};
    assert(!description.empty());
    ++i;
    assert(i >= 0);
    assert(i < static_cast<int>(text.size()));
    const std::string sequence = text[i];
    sequences.push_back(ribi::DnaSequence(description,sequence));
  }
  return sequences;
}


#ifndef NDEBUG
void FastaFile::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  using ribi::DnaSequence;
  {
    const std::vector<DnaSequence> alignments{
      DnaSequence("my_a","A")
    };
    const FastaFile file(alignments);
    std::stringstream s;
    s << file;
    assert(s.str() == ">my_a\nA\n");
  }
  {
    std::vector<DnaSequence> sequences{
      DnaSequence("my_a","A"),DnaSequence("my_b","C")
    };
    FastaFile file(sequences);
    std::stringstream s;
    s << file;
    assert(s.str() == ">my_a\nA\n>my_b\nC\n");
  }
  //File I/O
  {
    std::vector<DnaSequence> sequences{
      DnaSequence("my_a","A"),DnaSequence("my_b","C")
    };
    //Write to disc
    const std::string filename{"tmp.txt"};
    {
      const FastaFile file(sequences);
      std::ofstream f(filename.c_str());
      f << file;
    }
    //Read from disc
    const FastaFile file(filename);
    assert(file.GetSequences() == sequences);
  }
}
#endif


std::ostream& operator<<(std::ostream& os, const FastaFile file)
{
  for (const auto& p: file.GetSequences())
  {
    os
      << '>' << p.GetDescription() << '\n'
      << p.GetSequence() << '\n'
    ;
  }
  return os;
}
