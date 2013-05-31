#ifndef STANDARDWHITENOISESYSTEMPARAMETERS_H
#define STANDARDWHITENOISESYSTEMPARAMETERS_H

#include <boost/checked_delete.hpp>
#include "whitenoisesystemparameters.h"

struct StandardWhiteNoiseSystemParameters : public WhiteNoiseSystemParameters
{
  StandardWhiteNoiseSystemParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const { return WhiteNoiseSystemType::standard; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Check two parameter sets for equality using a fuzzy comparison
  static bool IsAboutEqual(const StandardWhiteNoiseSystemParameters& lhs, const StandardWhiteNoiseSystemParameters& rhs);

  private:
  ///Can only be deleted by boost::checked_delete
  ~StandardWhiteNoiseSystemParameters() {}
  friend void boost::checked_delete<>(StandardWhiteNoiseSystemParameters*);
};

#endif // STANDARDWHITENOISESYSTEMPARAMETERS_H
