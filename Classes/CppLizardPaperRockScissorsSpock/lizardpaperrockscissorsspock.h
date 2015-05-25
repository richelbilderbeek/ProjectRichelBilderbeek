#ifndef LIZARD_PAPER_ROCK_SCISSORS_SPOCK_H
#define LIZARD_PAPER_ROCK_SCISSORS_SPOCK_H

namespace ribi {

enum class LizardPaperRockScissorsSpock
{
  paper = 0,
  scissors = 1,
  rock = 2,
  spock = 3,
  lizard = 4
};

bool DoesBeat(
  const LizardPaperRockScissorsSpock lhs,
  const LizardPaperRockScissorsSpock rhs
);

#ifndef NDEBUG
void TestLizardPaperRockScissorsSpock() noexcept;
#endif // NDEBUG

} //~namespace ribi

#endif // LIZARD_PAPER_ROCK_SCISSORS_SPOCK_H
