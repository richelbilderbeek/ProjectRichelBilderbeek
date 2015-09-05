#ifndef MAZIAKTERMINAL_H
#define MAZIAKTERMINAL_H

#include "maziakdisplay.h"

namespace ribi {
namespace maziak {

struct MainDialog;

///Displays Maziak in command-line mode
struct Terminal : public Display
{
  Terminal();

  //Put the MainDialog on screen
  void DoDisplay(const MainDialog& main_dialog) override;

  bool GetDoShowSolution() override { --m_do_show_solution_cnt; return m_do_show_solution_cnt > 0; }

  int GetViewHeight() const noexcept override { return 20; }
  int GetViewWidth() const noexcept override { return 20; }

  ///Every turn, the animation must take place
  bool MustAnimateEnemiesAndPrisoners() noexcept override { return true; }

  std::set<Key> RequestKeys() override;

  void StartShowSolution() override { m_do_show_solution_cnt = 20; }


  private:
  int m_do_show_solution_cnt;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKTERMINAL_H
