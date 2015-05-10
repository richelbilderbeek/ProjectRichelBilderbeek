#ifndef NDEBUG
#include "parameters.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "loripesconsumptionfunction.h"
#include "testtimer.h"

void Parameters::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  using ribi::fileio::FileIo;
  //operator==
  {
    Parameters p;
    Parameters q;
    assert(p == q);
  }
  //Does loripes_consumption_function work?
  {
    const Parameters p = Parameters::GetTest(0);
    assert(p.loripes_consumption_function);
    assert(p.loripes_consumption_function.get());
    assert(p.loripes_consumption_function->CalculateConsumptionRate(
      p.initial_seagrass_density
    ) >= 0.0);
  }
  //Does loripes_consumption_function work after copying?
  {
    const Parameters p = Parameters::GetTest(0);
    assert(p.loripes_consumption_function);
    assert(p.loripes_consumption_function.get());
    assert(p.loripes_consumption_function->CalculateConsumptionRate(
      p.initial_seagrass_density
    ) >= 0.0);
    const Parameters q(p);
    assert(q.loripes_consumption_function);
    assert(q.loripes_consumption_function.get());
    assert(q.loripes_consumption_function->CalculateConsumptionRate(
      q.initial_seagrass_density
    ) >= 0.0);
  }
  //Set same loripes_consumption_function
  {
    Parameters p;
    p.loripes_consumption_function
      = std::make_shared<InvertedExponentialConsumption>(0.5)
    ;
    Parameters q;
    q.loripes_consumption_function
      = std::make_shared<InvertedExponentialConsumption>(0.5)
    ;
    if (p != q)
    {
      std::cerr << p << '\n' << q << '\n';
    }
    assert(p == q);
  }
  //Set different loripes_consumption_function
  {
    Parameters p;
    p.loripes_consumption_function
      = std::make_shared<InvertedExponentialConsumption>(0.5)
    ;
    Parameters q;
    q.loripes_consumption_function
      = std::make_shared<InvertedExponentialConsumption>(0.6)
    ;
    assert(p != q);
  }
  //Change sulfide_diffusion_rate
  {
    Parameters p;
    Parameters q;
    q.sulfide_diffusion_rate += 0.1;
    assert(p != q);
  }
  //File I/O
  {
    Parameters parameters;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters;
    }
    std::ifstream f(filename);
    Parameters parameters_too;
    f >> parameters_too;
    assert(parameters_too == parameters);
    FileIo().DeleteFile(filename);
  }
  //File I/O of initial_species_density
  {
    Parameters parameters;
    const ribi::units::SpeciesDensity d{
      23.45 * boost::units::si::species_per_square_meter
    };
    parameters.initial_seagrass_density = d;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters;
    }
    std::ifstream f(filename);
    Parameters parameters_too;
    f >> parameters_too;
    assert(parameters_too.initial_seagrass_density == d);
    assert(parameters_too == parameters);
    FileIo().DeleteFile(filename);
  }
}
#endif

