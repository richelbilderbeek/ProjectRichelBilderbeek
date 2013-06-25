#ifndef QTKALMANFILTEREXPERIMENTMODEL_H
#define QTKALMANFILTEREXPERIMENTMODEL_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/shared_ptr.hpp>
#include <map>

#include <QAbstractTableModel>
#include <QObject>
#include "kalmanfilterexperimentparametertype.h"
#include "kalmanfiltertype.h"
#include "kalmanfilter.h"
#include "whitenoisesystem.h"
#include "kalmanfilterexperiment.h"
#include "kalmanfilterexample.h"

///Contains all parameters and QAbstractTableModels for these
struct QtKalmanFilterExperimentModel : public QObject
{
  Q_OBJECT

  public:
  QtKalmanFilterExperimentModel();

  ///Calculate the optimal estimated Kalman gain
  void CalculateOptimalEstimatedKalmanGain();

  ///Create a KalmanFilterExperiment
  const boost::shared_ptr<KalmanFilterExperiment> CreateExperiment() const;

  ///Create a Kalman filter
  const boost::shared_ptr<KalmanFilter> CreateKalmanFilter() const;

  ///Create a Kalman filter its parameters
  const boost::shared_ptr<KalmanFilterParameters> CreateKalmanFilterParameters() const;

  ///Create a white noise system
  const boost::shared_ptr<WhiteNoiseSystem> CreateWhiteNoiseSystem() const;

  ///Create a white noise system parameter set
  const boost::shared_ptr<WhiteNoiseSystemParameters> CreateWhiteNoiseSystemParameters() const;

  ///Find the model for a parameter
  QAbstractTableModel * Find(KalmanFilterExperimentParameterType);
  const QAbstractTableModel * Find(KalmanFilterExperimentParameterType) const;

  ///Read the data from DokuWiki markup language
  void FromDokuWiki(const std::string& s);

  ///Read the data from HTML
  ///Not (yet?) implemented
  //void FromHtml(const std::string& s);

  ///Get the number of timesteps
  int GetNumberOfTimesteps() const { return m_number_of_timesteps; }

  ///Set an example parameter set
  void SetExample(const boost::shared_ptr<const KalmanFilterExample>& example);

  ///Set the type of Kalman filter
  void SetKalmanFilterType(const KalmanFilterType type);

  ///Set the estimated lag of a (possibly lagged) white noise system
  void SetLagEstimated(const int lag);

  ///Set the lag (of a lagged white noise system) in number of timesteps
  void SetLagReal(const int lag);

  ///Set the number of timesteps
  void SetNumberOfTimesteps(const int n);

  ///Set the type of white noise system
  void SetWhiteNoiseSystemType(const WhiteNoiseSystemType type);

  ///Convert the data to DokuWiki markup language
  const std::string ToDokuWiki() const;

  ///Convert the data to HTML
  const std::string ToHtml() const;

  private slots:
  ///If the state names are changed, let all other models have their headers updated
  void OnStateNamesChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

  private:
  ///The HTML description of the context of this experiment
  const std::string m_context;

  ///The Kalman filter type
  KalmanFilterType m_kalman_filter_type;

  ///The lag estimated to be in a white noise system
  int m_lag_estimated;

  ///The real lag (in a lagged white noise system)
  int m_lag_real;

  ///The map with all QAbstractTableModels
  const std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *> m_models;

  ///The number of timesteps desired
  int m_number_of_timesteps;

  ///The white noise system type
  WhiteNoiseSystemType m_white_noise_system_type;

  ///Create the map
  static const std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *> CreateMap();

  ///Create fixed-lag smoother Kalman filter parameters
  const boost::shared_ptr<KalmanFilterParameters> CreateFixedLagSmootherKalmanFilterParameters() const;

  ///Create standard Kalman filter parameters
  const boost::shared_ptr<StandardKalmanFilterParameters> CreateStandardKalmanFilterParameters() const;

  ///Create standard white noise system parameters
  const boost::shared_ptr<StandardWhiteNoiseSystemParameters> CreateStandardWhiteNoiseSystemParameters() const;

  ///Create lagged white noise system parameters
  const boost::shared_ptr<WhiteNoiseSystemParameters> CreateLaggedWhiteNoiseSystemParameters() const;

  ///Create steady-state Kalman filter parameters
  const boost::shared_ptr<KalmanFilterParameters> CreateSteadyStateKalmanFilterParameters() const;

  ///Create a model suiting a parameter
  static QAbstractTableModel * CreateModel(const KalmanFilterExperimentParameterType type);

  ///If the string holds a KalmanFilterType, set this class to hold the same value
  void ReadKalmanFilterType(const std::string& s);

  ///Search a string for a substring, check the end of the line for an int
  void Read(const std::string& line,const std::string& sub, int& value_to_change);

  ///Search a text for a name (which marks the start of a table), write the rest of the table to the model
  void Read(const std::vector<std::string>& text,const std::string& name, QAbstractTableModel * const model);

  ///If the string holds a WhiteNoiseSystemType, set this class to hold the same value
  void ReadWhiteNoiseSystemType(const std::string& s);

  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

bool operator==(const QtKalmanFilterExperimentModel lhs, const QtKalmanFilterExperimentModel rhs);

#endif // QTKALMANFILTEREXPERIMENTMODEL_H
