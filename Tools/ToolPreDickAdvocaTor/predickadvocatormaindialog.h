#ifndef PREDICKADVOCATORMAINDIALOG_H
#define PREDICKADVOCATORMAINDIALOG_H

#include <vector>
#include <string>

namespace ribi {

struct PreDickAdvocaTorMainDialog
{
  PreDickAdvocaTorMainDialog(const int seed);

  const std::vector<std::vector<int> > GetTeamScores() const noexcept { return m_team_scores; }
  static std::vector<std::string> GetTeamNames() noexcept;

  private:
  const std::vector<std::vector<int> > m_team_scores;
  static const std::vector<std::vector<int> > CreateTeamScores(const int seed);
  static int GetScore();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // PREDICKADVOCATORMAINDIALOG_H
