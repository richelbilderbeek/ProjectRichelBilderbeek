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
  int GetHeight() const noexcept { return m_height; }
  Initialization GetInitialization() const noexcept { return m_initialization; }
  int GetRngSeed() const noexcept { return m_rng_seed; }
  int GetWidth() const noexcept { return m_width; }

  void SetHeight(const int height);
  void SetInitialization(const Initialization initialization) noexcept;
  void SetRngSeed(const int rng_seed) noexcept;
  void SetWidth(const int width);

  private:
  int m_width;
  int m_height;
  Initialization m_initialization;
  int m_rng_seed;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const Parameters& parameters);
std::istream& operator>>(std::istream& is, Parameters& parameters);
bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept;

} //~namespace prswt { //Paper-Rock-Scissors-With-Trait
} //~namespace ribi

#endif // PAPERROCKSCISSORSWITHTRAITPARAMETERS_H
