#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "task.h"
//struct Task;

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
    const std::string& tasks_input_filename = "tasksfile.txt",
    const std::string& speciation_input_filename = "speciationrates.txt",
    const std::string& result_output_filename = "resultsfile.txt"
  ) : Simulation(
    ReadTasksFromFile(tasks_input_filename),
    ReadSpeciationRatesFromFile(speciation_input_filename),
    result_output_filename)
  {}

  ///Cleaner interface
  Simulation(
    const std::vector<Task>& tasks,
    const std::vector<double>& speciation_rates,
    const std::string& result_output_filename = "resultsfile.txt"
  );

  std::vector<double> GetSpeciesRichnesses() const noexcept { return m_species_richnesses; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  private:
  std::vector<double> m_species_richnesses;

};


#endif // SIMULATION_H
