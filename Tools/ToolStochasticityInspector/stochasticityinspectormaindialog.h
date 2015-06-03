#ifndef STOCHASTICITYINSPECTORMAINDIALOG_H
#define STOCHASTICITYINSPECTORMAINDIALOG_H

#include <vector>

namespace ribi { namespace ou { struct Parameters; } }
namespace ribi { namespace bm { struct Parameters; } }

struct StochasticityInspectorMainDialog
{
  StochasticityInspectorMainDialog();

  //Start with an Brownian Motion
  StochasticityInspectorMainDialog(
    const double init_x,
    const double t_end,
    const ribi::bm::Parameters& parameters
  );

  //Start with an Ornstein-Uhlenbeck process
  StochasticityInspectorMainDialog(
    const double init_x,
    const double dt,
    const double t_end,
    const ribi::ou::Parameters& parameters
  );

  const std::vector<double>& GetTimePoints() const noexcept { return  m_ts; }
  const std::vector<double>& GetValues() const noexcept { return m_xs; }


  private:
  std::vector<double> m_ts;
  std::vector<double> m_xs;
};

#endif // STOCHASTICITYINSPECTORMAINDIALOG_H
