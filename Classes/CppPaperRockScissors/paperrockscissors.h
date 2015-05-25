#ifndef PAPER_ROCK_SCISSORS_H
#define PAPER_ROCK_SCISSORS_H

namespace ribi {

enum class PaperRockScissors
{
  paper,
  rock,
  scissors
};

bool DoesBeat(const PaperRockScissors lhs, const PaperRockScissors rhs);

#ifndef NDEBUG
void TestPaperRockScissors() noexcept;
#endif //~NDEBUG

} //~namespace ribi

#endif // PAPER_ROCK_SCISSORS_H
