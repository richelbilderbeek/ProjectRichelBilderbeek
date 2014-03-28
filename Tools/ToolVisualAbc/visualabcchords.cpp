#include "visualabcchords.h"

std::vector<std::string> ribi::Chords::GetChords()
{
  std::vector<std::string> v;
  v.push_back("Am: A  C  E: [ACE]");
  v.push_back("C : G  C  E: [GCE]");
  v.push_back("Dm: A  D  F: [ADF]");
  v.push_back("E : G# B  E: [G#BE]");
  v.push_back("F : A  C  F: [ACF]");
  v.push_back("G : G  B  D: [GBD]");
  return v;
}

