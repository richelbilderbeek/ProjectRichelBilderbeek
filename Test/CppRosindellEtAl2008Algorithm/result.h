#ifndef RESULT_H
#define RESULT_H

#include <iosfwd>

// results file will contain all the results in rows of 6 entries
struct Result
{
  Result(
    const int survey_area_width,
    const int m_survey_area_height,
    const double m_speciation_rate,
    const double m_dispersal_distance,
    const bool m_dispersal_kernel_type,
    const double m_species_richness
  );

  double GetSpeciesRichness() const noexcept { return m_species_richness; }

  const int m_survey_area_width;
  const int m_survey_area_height;
  const double m_speciation_rate;
  const double m_dispersal_distance;
  const bool m_dispersal_kernel_type;
  const double m_species_richness; //The result
};

std::ostream& operator<<(std::ostream& os,const Result& result);

#endif // RESULT_H
