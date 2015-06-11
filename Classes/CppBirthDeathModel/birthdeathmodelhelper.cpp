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
#include "phylogeny_r.h"
#include "trace.h"
#include "ribi_rinside.h"

ribi::bdm::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::bdm::Helper::CalcLogLikelihood(
  const std::string& newick,
  const Rate& birth_rate,
  const Rate& death_rate
) const
{
  return CalcLogLikelihoodLaser(
    newick,
    birth_rate,
    death_rate
  );
}

double ribi::bdm::Helper::CalcLogLikelihoodDdd(
  const std::string& newick,
  const Rate& birth_rate,
  const Rate& death_rate
) const
{
  assert(!newick.empty());
  auto& r = ribi::Rinside().Get();

  r.parseEval("library(ape)");
  r.parseEval("library(DDD)");
  r["newick"] = newick;
  r.parseEval("phylogeny <- read.tree(text = newick)");
  r.parseEval("branch_lengths <- phylogeny$edge.length");
  r["lambda"] = birth_rate.value();
  r["mu"] = death_rate.value();

  // model of time-dependence:
  // - 0: no time dependence
  // - 1: speciation and/or extinction rate is exponentially declining with time
  // - 2: stepwise decline in speciation rate as in diversity-dependence without extinction
  // - 3: decline in speciation rate following deterministic logistic equation for ddmodel = 1
  r["model_of_time_dependence"] = 0;

  // conditioning:
  // - 0: conditioning on stem or crown age
  // - 1: conditioning on stem or crown age and non-extinction of the phylogeny
  // - 2: conditioning on stem or crown age and on the total number of extant taxa (including missing species)
  // - 3: conditioning on the total number of extant taxa (including missing species)
  r["conditioning"] = 1;

  // Likelihood of what:
  // - 0: branching times
  // - 1: the phylogeny
  r["likelihood_of_what"] = 1;

  // Show parameters and likelihood on screen:
  // - 0: no
  // - 1: yes
  r["show_parameters_and_likelihood_on_screen"] = 0;

  // first data point is:
  // - 1: stem age
  // - 2: crown age
  r["first_data_point_is"] = 2;

  r.parseEval(
    "log_likelihood_ddd_without_combinational_term <- bd_loglik("
    "  pars1 = c(lambda,mu),"
    "  pars2 = c("
    "    model_of_time_dependence,"
    "    conditioning,"
    "    likelihood_of_what,"
    "    show_parameters_and_likelihood_on_screen,"
    "    first_data_point_is"
    "  ),"
    "  brts=branch_lengths,"
    "  missnumspec = 0"
    ")"
  );

  r.parseEval(
    "log_likelihood_ddd <- log_likelihood_ddd_without_combinational_term / log(-0.6)"
  );
  Rcpp::DoubleVector v = r["log_likelihood_ddd"];
  assert(v.size() == 1);
  return v[0];
}

double ribi::bdm::Helper::CalcLogLikelihoodLaser(
  const std::string& newick,
  const Rate& birth_rate,
  const Rate& death_rate
) const
{
  assert(!newick.empty());
  auto& r = ribi::Rinside().Get();

  r.parseEval("library(ape)");
  r.parseEval("library(laser)");
  r["newick"] = newick;
  r.parseEval("phylogeny <- read.tree(text = newick)");
  r.parseEval("branch_lengths <- phylogeny$edge.length");
  r["lambda"] = birth_rate.value();
  r["mu"] = death_rate.value();
  Rcpp::DoubleVector v
    = r.parseEval("calcLHbd(x = branch_lengths, r = lambda - mu, a = mu / lambda)"
  );
  assert(v.size() == 1);
  return v[0];
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
    r.parseEval("library(ape)");
    r.parseEval("library(DDD)");
    r.parseEval("library(geiger)");
    r.parseEval("library(laser)");
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
  //CalcLogLikelihood
  {
    const std::string newick{"((F:2,G:2):1,H:3);"};
    const Rate& birth_rate{0.20 / boost::units::si::second};
    const Rate& death_rate{0.01 / boost::units::si::second};
    const double log_likelihood{
      h.CalcLogLikelihood(
        newick,
        birth_rate,
        death_rate
      )
    };
    assert(log_likelihood <= 0.0);
  }
  //CalcLogLikelihoodDdd and CalcLogLikelihoodLaser should give same results
  {
    const std::string newick{"((F:2,G:2):1,H:3);"};
    const Rate& birth_rate{0.20 / boost::units::si::second};
    const Rate& death_rate{0.01 / boost::units::si::second};
    const double log_likelihood_ddd{
      h.CalcLogLikelihoodDdd(
        newick,
        birth_rate,
        death_rate
      )
    };
    const double log_likelihood_laser{
      h.CalcLogLikelihoodLaser(
        newick,
        birth_rate,
        death_rate
      )
    };
    std::cout
      << "log_likelihood_laser: " << log_likelihood_laser << '\n'
      << "log_likelihood_ddd: " << log_likelihood_ddd << '\n'
    ;
    assert(abs(log_likelihood_laser - log_likelihood_ddd) < 0.0001);
  }

}
#endif
