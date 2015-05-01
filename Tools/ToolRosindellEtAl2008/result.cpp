#include "result.h"
#include <ostream>

Result::Result(
  const int survey_area_width,
  const int survey_area_height,
  const double speciation_rate,
  const double dispersal_distance,
  const DispersalKernel dispersal_kernel_type,
  const double species_richness
) : m_survey_area_width{survey_area_width},
    m_survey_area_height{survey_area_height},
    m_speciation_rate{speciation_rate},
    m_dispersal_distance{dispersal_distance},
    m_dispersal_kernel_type{dispersal_kernel_type},
    m_species_richness{species_richness}

{

}

std::ostream& operator<<(std::ostream& os,const Result& result)
{
  os
    << result.m_survey_area_width << " "
    << result.m_survey_area_height << " "
    << result.m_speciation_rate << " "
    << result.m_dispersal_distance << " "
    << ToStr(result.m_dispersal_kernel_type) << " "
    << result.m_species_richness
  ;
  return os;
}
