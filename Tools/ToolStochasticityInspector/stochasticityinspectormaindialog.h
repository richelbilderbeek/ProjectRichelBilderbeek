#ifndef STOCHASTICITYINSPECTORMAINDIALOG_H
#define STOCHASTICITYINSPECTORMAINDIALOG_H

#include <vector>
#include "ribi_time.h"

namespace ribi { namespace ou { struct Parameters; } }
namespace ribi { namespace bm { struct Parameters; } }

namespace ribi {

struct StochasticityInspectorMainDialog
{
  using Time = ribi::units::Time;

  ///H_0: data is created by a Brownian process
  ///H_1: data is created by an Ornstein Uhlenbeck process
  enum class HlrtResult { null_hypothesis_cannot_be_rejected, reject_null_hypothesis };

  StochasticityInspectorMainDialog();

  //Start with an Brownian Motion
  StochasticityInspectorMainDialog(
    const double init_x,
    const int t_end,
    const ribi::bm::Parameters& parameters
  );

  //Start with an Ornstein-Uhlenbeck process
  StochasticityInspectorMainDialog(
    const double init_x,
    const Time dt,
    const Time t_end,
    const ribi::ou::Parameters& parameters
  );

  double CalcBrownianMotionMaxLogLikelihood() const noexcept;
  double CalcOrnsteinUhlenbeckMaxLogLikelihood() const noexcept;

  HlrtResult DoHierarchicalLikelihoodRatioTest() const;


  const auto& GetTimePoints() const noexcept { return  m_ts; }
  const std::vector<double>& GetValues() const noexcept { return m_xs; }


  private:
  std::vector<Time> m_ts;
  std::vector<double> m_xs;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // STOCHASTICITYINSPECTORMAINDIALOG_H
