#include "dnasequence.h"

#include <cassert>
#include <stdexcept>

#ifndef NDEBUG
void ribi::DnaSequence::Test() noexcept
{
  {
    static bool is_tested {false};
    if (is_tested) return;
    is_tested = true;
  }
  //Recovery of parameters
  {
    const std::string description{"description"};
    const std::string sequence{"ACGT"};
    const DnaSequence s(description,sequence);
    assert(s.GetDescription() == description);
    assert(s.GetSequence() == sequence);
  }
  //operator==
  {
    const std::string description{"description"};
    const std::string sequence{"ACGT"};
    const DnaSequence s(description,sequence);
    const DnaSequence t(description,sequence);
    assert(s == t);
  }
  //operator!= on different description
  {
    const std::string sequence{"ACGT"};
    const DnaSequence s("description1",sequence);
    const DnaSequence t("description2",sequence);
    assert(s != t);
  }
  //operator!= on different sequence
  {
    const std::string description{"description"};
    const DnaSequence s(description,"ACGT");
    const DnaSequence t(description,"ACGTT");
    assert(s != t);
  }
  {
    try
    {
      DnaSequence s("description","incorrect_sequence");
      assert(!"Should not get here");
    }
    catch (std::logic_error&)
    {
      //Well detected!
    }
  }
}
#endif

