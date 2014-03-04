#include "openfoampatchfieldtypes.h"

#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/bimap.hpp>

#include "trace.h"

#pragma GCC diagnostic pop

boost::bimap<ribi::foam::PatchFieldType,std::string> ribi::foam::PatchFieldTypes::m_map;

const boost::bimap<ribi::foam::PatchFieldType,std::string> ribi::foam::PatchFieldTypes::CreateMap()
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<PatchFieldType,std::string> m;
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::advective,"advective"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::alphaSgsJayatillekeWallFunction,"alphaSgsJayatillekeWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::alphaSgsWallFunction,"alphaSgsWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::alphatJayatillekeWallFunction,"alphatJayatillekeWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::alphatWallFunction,"alphatWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::buoyantPressure,"buoyantPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::calculated,"calculated"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::codedFixedValue,"codedFixedValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::codedMixed,"codedMixed"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_epsilonWallFunction,"compressible_epsilonWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_kqRWallFunction,"compressible_kqRWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_omegaWallFunction,"compressible_omegaWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_temperatureThermoBaffle1D_constSolidThermoPhysics,"compressible_temperatureThermoBaffle1D_constSolidThermoPhysics"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_temperatureThermoBaffle1D_expoSolidThermoPhysics,"compressible_temperatureThermoBaffle1D_expoSolidThermoPhysics"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_turbulentHeatFluxTemperature,"compressible_turbulentHeatFluxTemperature"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_turbulentMixingLengthDissipationRateInlet,"compressible_turbulentMixingLengthDissipationRateInlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_turbulentMixingLengthFrequencyInlet,"compressible_turbulentMixingLengthFrequencyInlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_turbulentTemperatureCoupledBaffle,"compressible_turbulentTemperatureCoupledBaffle"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_turbulentTemperatureCoupledBaffleMixed,"compressible_turbulentTemperatureCoupledBaffleMixed"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::compressible_turbulentTemperatureRadCoupledMixed,"compressible_turbulentTemperatureRadCoupledMixed"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::cyclic,"cyclic"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::cyclicAMI,"cyclicAMI"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::cyclicSlip,"cyclicSlip"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::directionMixed,"directionMixed"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::empty,"empty"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::externalWallHeatFluxTemperature,"externalWallHeatFluxTemperature"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fan,"fan"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fanPressure,"fanPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedEnthalpy,"fixedEnthalpy"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedFluxPressure,"fixedFluxPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedGradient,"fixedGradient"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedInternalEnergy,"fixedInternalEnergy"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedInternalValue,"fixedInternalValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedPressureCompressibleDensity,"fixedPressureCompressibleDensity"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::fixedValue,"fixedValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::freestream,"freestream"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::freestreamPressure,"freestreamPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::gradientEnthalpy,"gradientEnthalpy"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::gradientInternalEnergy,"gradientInternalEnergy"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::htcConvection,"htcConvection"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::inletOutlet,"inletOutlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::inletOutletTotalTemperature,"inletOutletTotalTemperature"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mapped,"mapped"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mappedField,"mappedField"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mappedFixedInternalValue,"mappedFixedInternalValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mappedFixedPushedInternalValue,"mappedFixedPushedInternalValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mixed,"mixed"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mixedEnthalpy,"mixedEnthalpy"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mixedInternalEnergy,"mixedInternalEnergy"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::muSgsUSpaldingWallFunction,"muSgsUSpaldingWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::multiphaseFixedFluxPressure,"multiphaseFixedFluxPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mutLowReWallFunction,"mutLowReWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mutURoughWallFunction,"mutURoughWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mutUSpaldingWallFunction,"mutUSpaldingWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mutUWallFunction,"mutUWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mutkRoughWallFunction,"mutkRoughWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::mutkWallFunction,"mutkWallFunction"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::no_patch_field,"no_patch_field"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::nonuniformTransformCyclic,"nonuniformTransformCyclic"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::oscillatingFixedValue,"oscillatingFixedValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::outletInlet,"outletInlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::outletMappedUniformInlet,"outletMappedUniformInlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::partialSlip,"partialSlip"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::patch,"patch"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::phaseHydrostaticPressure,"phaseHydrostaticPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::processor,"processor"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::processorCyclic,"processorCyclic"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::rotatingTotalPressure,"rotatingTotalPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::sliced,"sliced"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::slip,"slip"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::symmetryPlane,"symmetryPlane"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::syringePressure,"syringePressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::timeVaryingMappedFixedValue,"timeVaryingMappedFixedValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::totalFlowRateAdvectiveDiffusive,"totalFlowRateAdvectiveDiffusive"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::totalPressure,"totalPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::totalTemperature,"totalTemperature"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::turbulentInlet,"turbulentInlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::turbulentIntensityKineticEnergyInlet,"turbulentIntensityKineticEnergyInlet"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::uniformDensityHydrostaticPressure,"uniformDensityHydrostaticPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::uniformFixedValue,"uniformFixedValue"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::uniformTotalPressure,"uniformTotalPressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::wallHeatTransfer,"wallHeatTransfer"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::waveSurfacePressure,"waveSurfacePressure"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::waveTransmissive,"waveTransmissive"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::wedge,"wedge"));
  m.insert(boost::bimap<PatchFieldType,std::string>::value_type(PatchFieldType::zeroGradient,"zeroGradient"));
  return m;
}

const std::vector<ribi::foam::PatchFieldType> ribi::foam::PatchFieldTypes::GetAllTypes()
{
  const std::vector<PatchFieldType> v {
    PatchFieldType::advective,
    PatchFieldType::alphaSgsJayatillekeWallFunction,
    PatchFieldType::alphaSgsWallFunction,
    PatchFieldType::alphatJayatillekeWallFunction,
    PatchFieldType::alphatWallFunction,
    PatchFieldType::buoyantPressure,
    PatchFieldType::calculated,
    PatchFieldType::codedFixedValue,
    PatchFieldType::codedMixed,
    PatchFieldType::compressible_epsilonWallFunction,
    PatchFieldType::compressible_kqRWallFunction,
    PatchFieldType::compressible_omegaWallFunction,
    PatchFieldType::compressible_temperatureThermoBaffle1D_constSolidThermoPhysics,
    PatchFieldType::compressible_temperatureThermoBaffle1D_expoSolidThermoPhysics,
    PatchFieldType::compressible_turbulentHeatFluxTemperature,
    PatchFieldType::compressible_turbulentMixingLengthDissipationRateInlet,
    PatchFieldType::compressible_turbulentMixingLengthFrequencyInlet,
    PatchFieldType::compressible_turbulentTemperatureCoupledBaffle,
    PatchFieldType::compressible_turbulentTemperatureCoupledBaffleMixed,
    PatchFieldType::compressible_turbulentTemperatureRadCoupledMixed,
    PatchFieldType::cyclic,
    PatchFieldType::cyclicAMI,
    PatchFieldType::cyclicSlip,
    PatchFieldType::directionMixed,
    PatchFieldType::empty,
    PatchFieldType::externalWallHeatFluxTemperature,
    PatchFieldType::fan,
    PatchFieldType::fanPressure,
    PatchFieldType::fixedEnthalpy,
    PatchFieldType::fixedFluxPressure,
    PatchFieldType::fixedGradient,
    PatchFieldType::fixedInternalEnergy,
    PatchFieldType::fixedInternalValue,
    PatchFieldType::fixedPressureCompressibleDensity,
    PatchFieldType::fixedValue,
    PatchFieldType::freestream,
    PatchFieldType::freestreamPressure,
    PatchFieldType::gradientEnthalpy,
    PatchFieldType::gradientInternalEnergy,
    PatchFieldType::htcConvection,
    PatchFieldType::inletOutlet,
    PatchFieldType::inletOutletTotalTemperature,
    PatchFieldType::mapped,
    PatchFieldType::mappedField,
    PatchFieldType::mappedFixedInternalValue,
    PatchFieldType::mappedFixedPushedInternalValue,
    PatchFieldType::mixed,
    PatchFieldType::mixedEnthalpy,
    PatchFieldType::mixedInternalEnergy,
    PatchFieldType::muSgsUSpaldingWallFunction,
    PatchFieldType::multiphaseFixedFluxPressure,
    PatchFieldType::mutLowReWallFunction,
    PatchFieldType::mutURoughWallFunction,
    PatchFieldType::mutUSpaldingWallFunction,
    PatchFieldType::mutUWallFunction,
    PatchFieldType::mutkRoughWallFunction,
    PatchFieldType::mutkWallFunction,
    PatchFieldType::no_patch_field,
    PatchFieldType::nonuniformTransformCyclic,
    PatchFieldType::oscillatingFixedValue,
    PatchFieldType::outletInlet,
    PatchFieldType::outletMappedUniformInlet,
    PatchFieldType::partialSlip,
    PatchFieldType::patch,
    PatchFieldType::phaseHydrostaticPressure,
    PatchFieldType::processor,
    PatchFieldType::processorCyclic,
    PatchFieldType::rotatingTotalPressure,
    PatchFieldType::sliced,
    PatchFieldType::slip,
    PatchFieldType::symmetryPlane,
    PatchFieldType::syringePressure,
    PatchFieldType::timeVaryingMappedFixedValue,
    PatchFieldType::totalFlowRateAdvectiveDiffusive,
    PatchFieldType::totalPressure,
    PatchFieldType::totalTemperature,
    PatchFieldType::turbulentInlet,
    PatchFieldType::turbulentIntensityKineticEnergyInlet,
    PatchFieldType::uniformDensityHydrostaticPressure,
    PatchFieldType::uniformFixedValue,
    PatchFieldType::uniformTotalPressure,
    PatchFieldType::wallHeatTransfer,
    PatchFieldType::waveSurfacePressure,
    PatchFieldType::waveTransmissive,
    PatchFieldType::wedge,
    PatchFieldType::zeroGradient
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(PatchFieldType::n_types));
  return v;
}

#ifndef NDEBUG
void ribi::foam::PatchFieldTypes::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const std::vector<PatchFieldType> v = GetAllTypes();
  const std::size_t sz = v.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    assert(i < v.size());
    const PatchFieldType t = v[i];
    const std::string s = ToStr(t);
    assert(!s.empty());
    const PatchFieldType u = ToType(s);
    assert(u == t);
  }
}
#endif

const std::string ribi::foam::PatchFieldTypes::ToStr(const PatchFieldType type)
{
  if (m_map.left.empty()) m_map = CreateMap();
  assert(!m_map.left.empty());
  assert(m_map.left.count(type) == 1);
  const std::string s = m_map.left.find(type)->second;
  return s;
}

ribi::foam::PatchFieldType ribi::foam::PatchFieldTypes::ToType(const std::string& s)
{
  if (m_map.right.empty()) m_map = CreateMap();
  assert(!m_map.right.empty());
  #ifndef NDEBUG
  if(m_map.right.count(s) != 1)
  {
    TRACE("ERROR");
    TRACE(s);
    TRACE(m_map.right.count(s));
  }

  #endif
  assert(m_map.right.count(s) == 1);
  const PatchFieldType t = m_map.right.find(s)->second;
  return t;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const PatchFieldType patch_field)
{
  os << PatchFieldTypes::ToStr(patch_field);
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, PatchFieldType& patch_field)
{
  std::string s;
  is >> s;
  patch_field = PatchFieldTypes::ToType(s);
  return is;
}
