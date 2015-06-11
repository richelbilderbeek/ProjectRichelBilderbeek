#include "birthdeathmodelhelper.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <boost/math/constants/constants.hpp>

#include "RInside.h"

#include "fileio.h"
#include "testtimer.h"
#include "birthdeathmodelparameters.h"
#include "trace.h"
#include "ribi_rinside.h"

ribi::bdm::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::bdm::Helper::CalcLogLikelihood(
  const std::vector<double>& v,
  const VolatilitySquared cand_volatility_squared
  //const double cand_volatility
) const
{
  assert(!v.empty());

  using boost::math::constants::two_pi;

  if (cand_volatility_squared == 0.0 / boost::units::si::second / boost::units::si::second) return 0.0; //TODO: allow this
  const double n{static_cast<double>(v.size())};
  const double log_likelihood{
    -((n/2.0)*std::log(cand_volatility_squared.value() * two_pi<double>()))
    - std::inner_product(
        std::begin(v)+1,
        std::end(v),
        std::begin(v),
        0.0,
        std::plus<double>(),
        [cand_volatility_squared](const double a, const double b)
        {
          return std::pow(a - b,2.0) / (2.0 * cand_volatility_squared.value());
        }
      )
  };
  return log_likelihood;
}

void ribi::bdm::Helper::CalcMaxLikelihood(
  const std::vector<double>& v,
  Volatility& volatility_hat
) const
{
  const bool verbose{false};
  const double n{static_cast<double>(v.size())};
  const double sum{
    std::inner_product(
      std::begin(v)+1,
      std::end(v),
      std::begin(v),
      0.0,
      std::plus<double>(),
      [](const double a, const double b)
      {
        return std::pow(a - b,2.0);
      }
    )
  };

  const double volatility_hat_squared{sum / n};

  if (verbose)
  {
    std::cout
      << "sum: " << sum << '\n'
      << "n: " << n << '\n'
      << "volatility_hat_squared: " << volatility_hat_squared << '\n'
    ;
  }
  volatility_hat = std::sqrt(volatility_hat_squared) / boost::units::si::second;
}

double ribi::bdm::Helper::CalcMaxLogLikelihood(
  const std::vector<double>& v
) const
{
  Volatility volatility_hat = 0.0 / boost::units::si::second;
  CalcMaxLikelihood(v,volatility_hat);
  return CalcLogLikelihood(v,volatility_hat * volatility_hat);
}


std::string ribi::bdm::Helper::CreateSimulatedPhylogeny(
  const Parameters& parameters
) const
{
  ribi::fileio::FileIo f;
  auto& r = ribi::Rinside().Get();

  r.parseEvalQ("library(ape)");
  r.parseEvalQ("library(geiger)");
  const double birth_rate{parameters.GetBirthRate().value()};
  const double death_rate{parameters.GetDeathRate().value()};
  const int n_taxa{parameters.GetNumberOfTaxa()};
  const int rng_seed{parameters.GetRngSeed()};
  const double t_end{parameters.GetTime().value()};

  assert(t_end == 0 && "Not yet implemented running to a certain time");

  r["birth_rate"] = birth_rate;
  r["death_rate"] = death_rate;
  r["n_taxa"] = n_taxa;
  r["rng_seed"] = rng_seed;
  r["t_end"] = t_end;
  // /home/richel/R/i686-pc-linux-gnu-library/3.1/Rcpp/include/Rcpp/vector/Vector.h
  assert(Rcpp::DoubleVector(r["birth_rate"])[0] == birth_rate);
  assert(Rcpp::DoubleVector(r["death_rate"])[0] == death_rate);
  assert(Rcpp::IntegerVector(r["n_taxa"])[0] == n_taxa);
  assert(Rcpp::IntegerVector(r["rng_seed"])[0] == rng_seed);
  assert(Rcpp::DoubleVector(r["t_end"])[0] == t_end);

  //Vital! If forgotten, the branch lengths will become N/A or 0
  std::setlocale(LC_ALL,"en_US.UTF-8");

  r.parseEvalQ("tree_full <- sim.bdtree(b=birth_rate,d=death_rate,stop=\"taxa\",n=n_taxa,extinct=FALSE,seed=rng_seed)");
  const Rcpp::String s = r.parseEval("write.tree(tree_full)");
  return std::string(s);
}

#ifndef NDEBUG
void ribi::bdm::Helper::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
    auto& r = ribi::Rinside().Get();
    r.parseEvalQ("library(ape)");
    r.parseEvalQ("library(geiger)");
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  Helper h;
  ribi::fileio::FileIo f;

  //CreateSimulatedPhylogeny must create a newick
  {
    const Parameters parameters(
      0.1 / boost::units::si::second,
      0.0 / boost::units::si::second,
      10,
      42
    );
    assert(!h.CreateSimulatedPhylogeny(parameters).empty());
  }
}
#endif
