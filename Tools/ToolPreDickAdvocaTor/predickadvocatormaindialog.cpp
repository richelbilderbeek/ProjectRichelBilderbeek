#include "predickadvocatormaindialog.h"

#include <cassert>
#include <cstdlib>

#include "trace.h"

ribi::PreDickAdvocaTorMainDialog::PreDickAdvocaTorMainDialog(const int seed)
  : m_team_scores(CreateTeamScores(seed))
{
  #ifndef NDEBUG
  Test();
  #endif
}

const std::vector<std::string> ribi::PreDickAdvocaTorMainDialog::GetTeamNames() noexcept
{
  std::vector<std::string> v;
  v.push_back("Algerije");
  v.push_back("Argentinie");
  v.push_back("Australie");
  v.push_back("Brazilie");
  v.push_back("Chili");
  v.push_back("Denemarken");
  v.push_back("Duitsland");
  v.push_back("Engeland");
  v.push_back("Frankrijk");
  v.push_back("Ghana");
  v.push_back("Griekenland");
  v.push_back("Honduras");
  v.push_back("Italie");
  v.push_back("Ivoorkust");
  v.push_back("Japan");
  v.push_back("Kameroen");
  v.push_back("Mexico");
  v.push_back("Nederland");
  v.push_back("Nieuw-Zeeland");
  v.push_back("Nigeria");
  v.push_back("Noord-Korea");
  v.push_back("Paraguay");
  v.push_back("Portugal");
  v.push_back("Servie");
  v.push_back("Slovenie");
  v.push_back("Slowakije");
  v.push_back("Spanje");
  v.push_back("USA");
  v.push_back("Uruguay");
  v.push_back("Zuid-Afrika");
  v.push_back("Zuid-Korea");
  v.push_back("Zwitserland");
  assert(v.size()==32);
  return v;
}

const std::vector<std::vector<int> > ribi::PreDickAdvocaTorMainDialog::CreateTeamScores(const int seed)
{
  const std::size_t sz { GetTeamNames().size() };
  std::vector<std::vector<int> > v(sz,std::vector<int>(sz,0));
  std::srand(seed);

  for (std::size_t y = 0; y!=sz; ++y)
  {
    for (std::size_t x = 0; x!=sz; ++x)
    {
      v[y][x] = GetScore();
    }
    //Add known score for The Netherlands
    v[y][17] = 0;
  }
  //Add known scores for The Netherlands
  v[17] = std::vector<int>(sz,10);

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
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PreDickAdvocaTorMainDialog::Test");
  TRACE("Finished ribi::PreDickAdvocaTorMainDialog::Test successfully");
}
#endif
