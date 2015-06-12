#ifndef RIBI_BEAST_H
#define RIBI_BEAST_H

#include <string>
#include <vector>

///Class to call BEAST2
struct Beast
{
  //Throws if BEAST2 cannot be found
  Beast();


  void AnalyzeBirthDeath(
    const std::string& log_file,
    const std::string png_filename
  ) const;

  void AnalyzeCoalescent(
    const std::string& log_file,
    const std::string png_filename_coalescent_constant,
    const std::string png_filename_popsize
  ) const;

  void Run(
    const std::string& xml_input_filename,
    const std::string& log_output_filename,
    const std::string& trees_output_filename
  ) const noexcept;

  private:
  static const std::string sm_beast_path;

  void AnalyzeBirthDeathRinside(
    const std::string& log_file,
    const std::string png_filename
  ) const;

  void AnalyzeBirthDeathRscript(
    const std::string& log_file,
    const std::string png_filename
  ) const;

  void AnalyzeCoalescentRinside(
    const std::string& log_file,
    const std::string png_filename_coalescent_constant,
    const std::string png_filename_popsize
  ) const;

  void AnalyzeCoalescentRscript(
    const std::string& log_file,
    const std::string png_filename_coalescent_constant,
    const std::string png_filename_popsize
  ) const;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif //RIBI_BEAST_H
