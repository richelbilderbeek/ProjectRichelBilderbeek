#include "paperrockscissorswithtraitparameters.h"

ribi::prswt::Parameters::Parameters(
  const int width,
  const int height,
  const Initialization initialization,
  const int rng_seed
) : m_width{width},
    m_height{height},
    m_initialization{initialization},
    m_rng_seed{rng_seed}
{

}
