#include "sequence.h"

#include <cassert>
#include <stdexcept>

#ifndef NDEBUG
void Sequence::Test() noexcept
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
    const Sequence s(description,sequence);
    assert(s.GetDescription() == description);
    assert(s.GetSequence() == sequence);
  }
  //operator==
  {
    const std::string description{"description"};
    const std::string sequence{"ACGT"};
    const Sequence s(description,sequence);
    const Sequence t(description,sequence);
    assert(s == t);
  }
  //operator!= on different description
  {
    const std::string sequence{"ACGT"};
    const Sequence s("description1",sequence);
    const Sequence t("description2",sequence);
    assert(s != t);
  }
  //operator!= on different sequence
  {
    const std::string description{"description"};
    const Sequence s(description,"ACGT");
    const Sequence t(description,"ACGTT");
    assert(s != t);
  }
  {
    try
    {
      Sequence s("description","incorrect_sequence");
      assert(!"Should not get here");
    }
    catch (std::logic_error&)
    {
      //Well detected!
    }
  }
}
#endif

