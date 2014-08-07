#include "predickadvocatormaindialog.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

#include "testtimer.h"
#include "trace.h"

ribi::PreDickAdvocaTorMainDialog::PreDickAdvocaTorMainDialog(const int seed)
  : m_team_scores(CreateTeamScores(seed))
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<std::string> ribi::PreDickAdvocaTorMainDialog::GetTeamNames() noexcept
{
  const std::vector<std::string> v {
    "Algeria",
    "Argentina",
    "Australia",
    "Belgium",
    "Bosnia and Herzegovina",
    "Brazil",
    "Cameroon",
    "Chile",
    "Colombia",
    "Costa Rica",
    "Croatia",
    "Ecuador",
    "England",
    "France",
    "Germany",
    "Ghana",
    "Greece",
    "Honduras",
    "Iran",
    "Italy",
    "Ivory Coast",
    "Japan",
    "Mexico",
    "Netherlands",
    "Nigeria",
    "Portugal",
    "Russia",
    "South Korea",
    "Spain",
    "Switzerland",
    "United States",
    "Uruguay"
  };
  assert(v.size()==32);
  return v;
}

const std::vector<std::vector<int> > ribi::PreDickAdvocaTorMainDialog::CreateTeamScores(const int seed)
{
  const std::vector<std::string> team_names { GetTeamNames() };
  const std::size_t sz { team_names.size() };
  std::vector<std::vector<int> > v(sz,std::vector<int>(sz,0));
  std::srand(seed);


  const std::size_t dutch_index
    = std::distance(
      team_names.begin(),
      std::find(team_names.begin(),team_names.end(),"Netherlands")
    );
  assert(dutch_index < sz);
  assert(GetTeamNames()[dutch_index] == "Netherlands");
  for (std::size_t y = 0; y!=sz; ++y)
  {
    for (std::size_t x = 0; x!=sz; ++x)
    {
      v[y][x] = GetScore();
    }
    //Add known score for The Netherlands
    v[y][dutch_index] = 0;
  }
  //Add known scores for The Netherlands
  v[dutch_index] = std::vector<int>(sz,10);

  return v;
}

int ribi::PreDickAdvocaTorMainDialog::GetScore()
{
  const int max_score = 9;
  int r = std::rand() % 256;
  for (int score=0; score!=max_score; ++score)
  {
    if ((r%2)==1) return score;
    r >>= 1;
  }
  return max_score;
}

#ifndef NDEBUG
void ribi::PreDickAdvocaTorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
