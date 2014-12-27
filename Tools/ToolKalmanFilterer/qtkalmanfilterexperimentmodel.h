#ifndef QTKALMANFILTEREXPERIMENTMODEL_H
#define QTKALMANFILTEREXPERIMENTMODEL_H

#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QAbstractTableModel>
#include <QObject>

#include <boost/signals2.hpp>
#pragma GCC diagnostic pop
#include "kalmanfilterexperimentparametertype.h"
#include "kalmanfiltertype.h"
#include "kalmanfilter.h"
#include "whitenoisesystem.h"
#include "kalmanfilterexperiment.h"
#include "kalmanfilterexample.h"

namespace ribi {
namespace kalman {

///Contains all parameters and QAbstractTableModels for these
struct QtKalmanFilterExperimentModel : public QObject
{
  Q_OBJECT

  public:

  explicit QtKalmanFilterExperimentModel(QObject *parent = 0) noexcept;

  ///Calculate the optimal estimated Kalman gain
  void CalculateOptimalEstimatedKalmanGain() noexcept;

  ///Create a KalmanFilterExperiment
  boost::shared_ptr<KalmanFilterExperiment> CreateExperiment() const noexcept;

  ///Create a Kalman filter
  boost::shared_ptr<KalmanFilter> CreateKalmanFilter() const;

  ///Create a Kalman filter its parameters
  boost::shared_ptr<KalmanFilterParameters> CreateKalmanFilterParameters() const noexcept;

  ///Create a white noise system
  boost::shared_ptr<WhiteNoiseSystem> CreateWhiteNoiseSystem() const noexcept;

  ///Create a white noise system parameter set
  boost::shared_ptr<WhiteNoiseSystemParameters> CreateWhiteNoiseSystemParameters() const noexcept;

  ///Find the model for a parameter
  QAbstractTableModel * Find(KalmanFilterExperimentParameterType);
  const QAbstractTableModel * Find(KalmanFilterExperimentParameterType) const;

  ///Read the data from DokuWiki markup language
  void FromDokuWiki(const std::string& s);

  ///Read the data from HTML
  ///Not (yet?) implemented
  //void FromHtml(const std::string& s);

  ///Set the context
  const std::string& GetContext() const noexcept { return m_context; }

  ///Get the number of timesteps
  int GetNumberOfTimesteps() const noexcept { return m_number_of_timesteps; }

  ///Set the context
  void SetContext(const std::string& context);

  ///Set an example parameter set
  void SetExample(const boost::shared_ptr<const KalmanFilterExample>& example) noexcept;

  ///Set the type of Kalman filter
  void SetKalmanFilterType(const KalmanFilterType type) noexcept;

  ///Set the estimated lag of a (possibly lagged) white noise system
  void SetLagEstimated(const int lag);

  ///Set the lag (of a lagged white noise system) in number of timesteps
  void SetLagReal(const int lag) noexcept;

  ///Set the number of timesteps
  void SetNumberOfTimesteps(const int n) noexcept;

  ///Set the type of white noise system
  void SetWhiteNoiseSystemType(const WhiteNoiseSystemType type) noexcept;

  ///Convert the data to DokuWiki markup language
  std::string ToDokuWiki() const noexcept;

  ///Convert the data to HTML
  std::string ToHtml() const noexcept;

  ///Emitted when the context changes
  boost::signals2::signal<void(const std::string)> m_signal_context_changed;

  ///Emitted when the Kalman filter type changes
  boost::signals2::signal<void(KalmanFilterType)> m_signal_kalman_filter_type_changed;

  ///Emitted when the white noise system type changes
  boost::signals2::signal<void(int)> m_signal_number_of_timesteps_changed;

  ///Emitted when the white noise system type changes
  boost::signals2::signal<void(WhiteNoiseSystemType)> m_signal_white_noise_system_type_changed;

  private slots:
  ///If the state names are changed, let all other models have their headers updated
  void OnStateNamesChanged();

  private:
  ///The HTML description of the context of this experiment
  std::string m_context;

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

  ///The version number
  ///0: version before this numbering existed
  ///1: since 2013-06-28
  ///2: since 2013-07-02
  int m_version;

  ///The current version number, the version of the output this class now produces
  static const int m_version_current;

  ///The white noise system type
  WhiteNoiseSystemType m_white_noise_system_type;

  ///Create the map
  static std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *> CreateMap() noexcept;

  ///Create fixed-lag smoother Kalman filter parameters
  boost::shared_ptr<KalmanFilterParameters> CreateFixedLagSmootherKalmanFilterParameters() const noexcept;

  ///Create standard Kalman filter parameters
  boost::shared_ptr<StandardKalmanFilterParameters> CreateStandardKalmanFilterParameters() const noexcept;

  ///Create standard white noise system parameters
  boost::shared_ptr<StandardWhiteNoiseSystemParameters> CreateStandardWhiteNoiseSystemParameters() const noexcept;

  ///Create gaps-filled white noise system parameters
  boost::shared_ptr<WhiteNoiseSystemParameters> CreateGapsFilledWhiteNoiseSystemParameters() const noexcept;

  ///Create lagged white noise system parameters
  boost::shared_ptr<WhiteNoiseSystemParameters> CreateLaggedWhiteNoiseSystemParameters() const noexcept;

  ///Create steady-state Kalman filter parameters
  boost::shared_ptr<KalmanFilterParameters> CreateSteadyStateKalmanFilterParameters() const noexcept;

  ///Create a model suiting a parameter
  static QAbstractTableModel * CreateModel(const KalmanFilterExperimentParameterType type) noexcept;

  #ifndef NDEBUG
  bool IsValid() const;
  #endif

  ///If the text holds an HTML context, set this class to hold the same value
  void ReadContext(const std::vector<std::string>& s);

  ///If the string holds a KalmanFilterType, set this class to hold the same value
  void ReadKalmanFilterType(const std::string& s);

  ///Search a string for a substring, check the end of the line for an int
  void Read(const std::string& line,const std::string& sub, int& value_to_change);

  ///Search a text for a name (which marks the start of a table), write the rest of the table to the model
  void Read(const std::vector<std::string>& text,const std::string& name, QAbstractTableModel * const model);

  ///If the string holds a WhiteNoiseSystemType, set this class to hold the same value
  void ReadWhiteNoiseSystemType(const std::string& s);

  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator
  );
  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif
};

bool operator==(const QtKalmanFilterExperimentModel& lhs, const QtKalmanFilterExperimentModel& rhs) noexcept;

} //~namespace kalman
} //~namespace ribi

#endif // QTKALMANFILTEREXPERIMENTMODEL_H
