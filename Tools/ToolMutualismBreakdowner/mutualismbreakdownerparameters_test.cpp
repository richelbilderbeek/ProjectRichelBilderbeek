#ifndef NDEBUG
#include "mutualismbreakdownerparameters.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <boost/units/io.hpp>

#include "fileio.h"
#include "mutualismbreakdownersulfideconsumptionfunction.h"
#include "testtimer.h"

void ribi::mb::Parameters::Test() noexcept
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
  //DeltaT
  //Does sulfide_consumption_function work?
  {
    const Parameters p = Parameters::GetTest(0);
    assert(p.m_sulfide_consumption_function);
    assert(p.m_sulfide_consumption_function.get());
    assert(p.m_sulfide_consumption_function->CalculateConsumption(
      p.m_initial_sulfide_concentration,
      p.m_initial_loripes_density
    ).value() >= 0.0);
  }
  //Does sulfide_consumption_function work after copying?
  {
    const Parameters p = Parameters::GetTest(0);
    assert(p.m_sulfide_consumption_function);
    assert(p.m_sulfide_consumption_function.get());
    assert(p.m_sulfide_consumption_function->CalculateConsumption(
      p.m_initial_sulfide_concentration,
      p.m_initial_loripes_density
    ).value() >= 0.0);
    const Parameters q(p);
    assert(q.m_sulfide_consumption_function);
    assert(q.m_sulfide_consumption_function.get());
    assert(q.m_sulfide_consumption_function->CalculateConsumption(
      q.m_initial_sulfide_concentration,
      q.m_initial_loripes_density
    ).value() >= 0.0);
  }
  //Set same sulfide_consumption_function
  {
    Parameters p;
    p.m_sulfide_consumption_function
      = std::make_shared<LinearConsumption>(0.5)
    ;
    Parameters q;
    q.m_sulfide_consumption_function
      = std::make_shared<LinearConsumption>(0.5)
    ;
    if (p != q)
    {
      std::cerr << p << '\n' << q << '\n';
    }
    assert(p == q);
  }
  //Set different sulfide_consumption_function
  {
    Parameters p;
    p.m_sulfide_consumption_function
      = std::make_shared<LinearConsumption>(0.5)
    ;
    Parameters q;
    q.m_sulfide_consumption_function
      = std::make_shared<LinearConsumption>(0.6)
    ;
    assert(p != q);
  }
  //Change of initial_loripes_density
  {
    Parameters p;
    Parameters q;
    q.m_initial_loripes_density
      = p.m_initial_loripes_density
      + (0.1 * boost::units::si::species_per_square_meter)
    ;
    assert(p != q);

  }
  //File I/O, one Parameters
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
  //File I/O, two Parameters
  {
    Parameters parameters_a;
    Parameters parameters_b;
    const std::string filename{
      FileIo().GetTempFileName(".txt")
    };
    {
      std::ofstream f(filename);
      f << parameters_a << " " << parameters_b;
    }
    std::ifstream f(filename);
    Parameters parameters_a_too;
    Parameters parameters_b_too;
    f >> parameters_a_too >> parameters_b_too;
    assert(parameters_a_too == parameters_a);
    assert(parameters_b_too == parameters_b);
    FileIo().DeleteFile(filename);
  }
  //File I/O of initial_species_density
  {
    Parameters parameters;
    const ribi::units::SpeciesDensity d{
      23.45 * boost::units::si::species_per_square_meter
    };
    parameters.m_initial_seagrass_density = d;
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
    assert(parameters_too.m_initial_seagrass_density == d);
    assert(parameters_too == parameters);
    FileIo().DeleteFile(filename);
  }
}
#endif

