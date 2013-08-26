//---------------------------------------------------------------------------

#ifndef UnitCdPlayerH
#define UnitCdPlayerH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UnitController.h"
#include "UnitMachine.h"
#include "UnitTapButton.h"
struct AudioSignalDisplay;
struct CinchRedFemale;
struct CinchWhiteFemale;
struct Connector;
struct InternalConnection;
struct LcdSymbol;
struct Led;
struct Plug220;
struct PressButton;
struct TFormCdPlayer;
//---------------------------------------------------------------------------
struct CdPlayer : public Machine
{
  CdPlayer();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int) const { return 0.0; };
  //Does the machine have power?
  const bool HasPower() const;

  void PressPower();
  void PressRecord();
  void PressStop();
  void PressPlay();
  void Tick(); //Must be called every time cycle for recording and playing

  private:

  enum CdPlayerState { cdOff, cdOn, cdPlay };
  CdPlayerState mState;

  const std::vector<double> mAudioRecordedL;
  const std::vector<double> mAudioRecordedR;
  int mPlayPos;
  static const int mAudioRecordedLength = 100;

  const std::vector<double> CreateCdL() const;
  const std::vector<double> CreateCdR() const;


  ~CdPlayer() {}
  //CdPlayer can only be deleted by boost::shared_ptr
  friend boost::checked_delete(CdPlayer *);

  //View
  //Use
  boost::shared_ptr< TapButton<CdPlayer> > mButtonPower;
  boost::shared_ptr< TapButton<CdPlayer> > mButtonStop;
  boost::shared_ptr< TapButton<CdPlayer> > mButtonPlay;
  //Connect
  boost::shared_ptr<CinchWhiteFemale> mCinchFemaleOutL;
  boost::shared_ptr<CinchRedFemale> mCinchFemaleOutR;
  boost::shared_ptr<Plug220> mPlug220Power;
  boost::shared_ptr<InternalConnection> mConnectionAudioSignalL;
  boost::shared_ptr<InternalConnection> mConnectionAudioSignalR;
  boost::shared_ptr<InternalConnection> mConnectionLcdSymbolPlay;
  boost::shared_ptr<InternalConnection> mConnectionLedPower;
  //Display
  boost::shared_ptr<AudioSignalDisplay> mAudioSignalDisplayL;
  boost::shared_ptr<AudioSignalDisplay> mAudioSignalDisplayR;
  boost::shared_ptr<LcdSymbol> mLcdSymbolPlay;
  boost::shared_ptr<Led> mLedPower;

  friend TFormCdPlayer;
};
//---------------------------------------------------------------------------
#endif
