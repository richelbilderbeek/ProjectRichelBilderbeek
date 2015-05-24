#ifndef PAPERROCKSCISSORSWITHTRAITPARAMETERS_H
#define PAPERROCKSCISSORSWITHTRAITPARAMETERS_H

#include "paperrockscissorswithtraitinitialization.h"

namespace ribi {
namespace prswt { //Paper-Rock-Scissors-With-Trait

struct Parameters
{
  Parameters(
    const int width,
    const int height,
    const Initialization initialization,
    const int rng_seed
  );
  int GetWidth() const noexcept { return m_width; }
  int GetHeight() const noexcept { return m_height; }
  Initialization GetInitialization() const noexcept { return m_initialization; }
  int GetRngSeed() const noexcept { return m_rng_seed; }
  void SetInitialization(const Initialization initialization) noexcept { m_initialization = initialization; }

  private:
  int m_width;
  int m_height;
  Initialization m_initialization;
  int m_rng_seed;
};

} //~namespace prswt { //Paper-Rock-Scissors-With-Trait
} //~namespace ribi

#endif // PAPERROCKSCISSORSWITHTRAITPARAMETERS_H
