#ifndef BIRTHDEATHMODELHELPER_H
#define BIRTHDEATHMODELHELPER_H

#include "rate.h"
#include <vector>

namespace ribi {
namespace bdm {

struct Parameters;

struct Helper
{
  using Rate = ribi::units::Rate;

  Helper();

  ///Calculate the likelihood of the candidate parameters in generating the dataset
  double CalcLogLikelihood(
    const std::string& newick,
    const Rate& birth_rate,
    const Rate& death_rate
  ) const;

  std::string CreateSimulatedPhylogeny(
    const Parameters& parameters
  ) const;

  private:

  ///Uses DDD package
  double CalcLogLikelihoodDdd(
    const std::string& newick,
    const Rate& birth_rate,
    const Rate& death_rate
  ) const;

  ///Uses laser package
  double CalcLogLikelihoodLaser(
    const std::string& newick,
    const Rate& birth_rate,
    const Rate& death_rate
  ) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace bm
} //~namespace ribi

#endif // BIRTHDEATHMODELHELPER_H
