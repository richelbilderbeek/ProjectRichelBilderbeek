#ifndef QTKALMANFILTERERMODEL_H
#define QTKALMANFILTERERMODEL_H

#include "qtublasmatrixdoublemodel.h"
#include "qtublasvectordoublemodel.h"
#include "qtublasvectorintmodel.h"
#include "qtstdvectorfunctionmodel.h"
#include "qtstdvectorstringmodel.h"

namespace ribi {

//struct QtUblasMatrixDoubleModel;
typedef QtUblasMatrixDoubleModel ControlModel;
typedef QtUblasMatrixDoubleModel EstimatedMeasurementNoiseModel;
typedef QtUblasMatrixDoubleModel EstimatedOptimalKalmanGainModel;
typedef QtUblasMatrixDoubleModel EstimatedProcessNoiseCovarianceModel;
typedef QtUblasMatrixDoubleModel InitialCovarianceEstimateModel;
typedef QtUblasMatrixDoubleModel ObservationModel;
typedef QtUblasMatrixDoubleModel StateTransitionModel;

//struct QtStdVectorDoubleModel;
typedef QtUblasVectorDoubleModel InitialStateEstimateModel;
typedef QtUblasVectorDoubleModel InitialStateRealModel;
typedef QtUblasVectorDoubleModel RealMeasurementNoiseModel;
typedef QtUblasVectorDoubleModel RealProcessNoiseModel;

//struct QtStdVectorIntModel;
typedef QtUblasVectorIntModel MeasurementFrequencyModel;

//struct QtStdVectorFunctionModel;
typedef QtStdVectorFunctionModel InputModel;

//struct QtStdVectorStringModel;
typedef QtStdVectorStringModel StateNamesModel;

} //~namespace ribi

#endif // QTKALMANFILTERERMODEL_H
