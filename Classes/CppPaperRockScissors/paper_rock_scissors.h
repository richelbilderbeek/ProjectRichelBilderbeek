#ifndef PAPER_ROCK_SCISSORS_H
#define PAPER_ROCK_SCISSORS_H

enum class PaperRockScissors
{
  paper,
  rock,
  scissors
};

bool DoesBeat(const PaperRockScissors lhs, const PaperRockScissors rhs);
void TestPaperRockScissors() noexcept;

#endif // PAPER_ROCK_SCISSORS_H
