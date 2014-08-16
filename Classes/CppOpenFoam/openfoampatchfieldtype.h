#ifndef RIBI_OPENFOAMPATCHFIELDTYPE_H
#define RIBI_OPENFOAMPATCHFIELDTYPE_H

namespace ribi {
namespace foam {

/// From http://openfoam.org/docs/user/mesh-description.php, pragraph 5.1.1.4 Boundary:
///   A boundary is a list of patches, each of which is associated with a boundary condition.
///   A patch is a list of face labels which clearly must contain only boundary faces
///   and no internal faces. The boundary is required to be closed,
///   i.e. the sum all boundary face area vectors equates to zero to machine tolerance.
/// To indicate internal faces, use no_patch_field
enum class PatchFieldType {
  advective,
  alphaSgsJayatillekeWallFunction,
  alphaSgsWallFunction,
  alphatJayatillekeWallFunction,
  alphatWallFunction,
  buoyantPressure,
  calculated,
  codedFixedValue,
  codedMixed,
  compressible_epsilonWallFunction,
  compressible_kqRWallFunction,
  compressible_omegaWallFunction,
  compressible_temperatureThermoBaffle1D_constSolidThermoPhysics,
  compressible_temperatureThermoBaffle1D_expoSolidThermoPhysics,
  compressible_turbulentHeatFluxTemperature,
  compressible_turbulentMixingLengthDissipationRateInlet,
  compressible_turbulentMixingLengthFrequencyInlet,
  compressible_turbulentTemperatureCoupledBaffle,
  compressible_turbulentTemperatureCoupledBaffleMixed,
  compressible_turbulentTemperatureRadCoupledMixed,
  cyclic,
  cyclicAMI,
  cyclicSlip,
  directionMixed,
  empty,
  externalWallHeatFluxTemperature,
  fan,
  fanPressure,
  fixedEnthalpy,
  fixedFluxPressure,
  fixedGradient,
  fixedInternalEnergy,
  fixedInternalValue,
  fixedPressureCompressibleDensity,
  fixedValue,
  freestream,
  freestreamPressure,
  gradientEnthalpy,
  gradientInternalEnergy,
  htcConvection,
  inletOutlet,
  inletOutletTotalTemperature,
  mapped,
  mappedField,
  mappedFixedInternalValue,
  mappedFixedPushedInternalValue,
  mixed,
  mixedEnthalpy,
  mixedInternalEnergy,
  muSgsUSpaldingWallFunction,
  multiphaseFixedFluxPressure,
  mutLowReWallFunction,
  mutURoughWallFunction,
  mutUSpaldingWallFunction,
  mutUWallFunction,
  mutkRoughWallFunction,
  mutkWallFunction,
  no_patch_field, //To indicate that a 'no boundary'; that is, an internal face
  nonuniformTransformCyclic,
  oscillatingFixedValue,
  outletInlet,
  outletMappedUniformInlet,
  partialSlip,
  patch,
  phaseHydrostaticPressure,
  processor,
  processorCyclic,
  rotatingTotalPressure,
  sliced,
  slip,
  symmetryPlane,
  syringePressure,
  timeVaryingMappedFixedValue,
  totalFlowRateAdvectiveDiffusive,
  totalPressure,
  totalTemperature,
  turbulentInlet,
  turbulentIntensityKineticEnergyInlet,
  uniformDensityHydrostaticPressure,
  uniformFixedValue,
  uniformTotalPressure,
  wall, //Used for defaultFaces
  wallHeatTransfer,
  waveSurfacePressure,
  waveTransmissive,
  wedge,
  zeroGradient,
  n_types //Used for debugging only, keep at last position
};

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMPATCHFIELDTYPE_H
