#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "rng.h"
#include "task.h"
#include "result.h"

std::vector<double> ReadSpeciationRatesFromFile(
  const std::string& speciation_input_filename
);

struct Simulation
{
  ///Maintain interface of original article
  ///tasks_input_filename: the file that contains a list of simulations that are required
  ///speciation_input_filename: a list of speciation rates we wish to simulate
  ///result_output_filename: the file that will output the results of the simulations to
  Simulation(
    const Rng::Type rng_type,
    const std::string& tasks_input_filename = "tasksfile.txt",
    const std::string& speciation_input_filename = "speciationrates.txt",
    const std::string& result_output_filename = "resultsfile.txt"
  ) : Simulation(
    ReadTasksFromFile(tasks_input_filename),
    ReadSpeciationRatesFromFile(speciation_input_filename),
    rng_type,
    result_output_filename)
  {}

  ///Cleaner interface
  Simulation(
    const std::vector<Task>& tasks,
    const std::vector<double>& speciation_rates,
    const Rng::Type rng_type = Rng::Type::rosindell,
    const std::string& result_output_filename = "resultsfile.txt",
    const int seed = 4,
    const bool verbose = true
  );


  std::vector<Result> GetResults() const noexcept { return m_results; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:

  std::vector<Result> m_results;

  const bool m_verbose;

};


#endif // SIMULATION_H
