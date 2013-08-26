//---------------------------------------------------------------------------

#ifndef UnitConnectorControlH
#define UnitConnectorControlH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
struct Connector;
struct TFormSprites;
struct TFormMachine;
struct CinchRedFemale;
struct CinchRedMale;
struct CinchWhiteFemale;
struct CinchWhiteMale;
struct DmxFemale;
struct DmxMale;
struct EuroFemale;
struct EuroMale;
struct JackFemale;
struct JackXlrFemale; //Combo connector of both Jack female and XLR female
struct JackMale;
struct Plug220;
struct Socket220;
struct SocketPowerFemale;
struct SocketPowerMale;
struct SpeakonFemale;
struct SpeakonMale;
struct XlrFemale;
struct XlrMale;
namespace Extctrls { struct TImage; }
//---------------------------------------------------------------------------
//Handles the GUI of a Connector
struct ConnectorControl
{
  ConnectorControl(
    TFormMachine * const belongsTo,
    Extctrls::TImage * const image,
    const Extctrls::TImage * const imageUnselectedUnconnected,
    const Extctrls::TImage * const imageSelectedUnconnected,
    const Extctrls::TImage * const imageUnselectedConnected,
    const Extctrls::TImage * const imageSelectedConnected);

  void Select();
  void Unselect();
  void Connect(ConnectorControl * const otherConnectorControl);
  void Disconnect();
  const bool CanConnect(ConnectorControl * const otherConnectorControl) const;

  virtual const Connector * const GetConnector() const = 0;
  virtual Connector * GetConnector() = 0;

  const bool IsConnected() const;
  const bool IsConnectedTo(const ConnectorControl * other) const;

  protected:
  //ConnectorControl can only be deleted by boost::shared_ptr
  //or its descendants
  virtual ~ConnectorControl() {}
  friend boost::checked_delete(ConnectorControl*);

  const Extctrls::TImage * const mImageUnselectedUnconnected;
  const Extctrls::TImage * const mImageSelectedUnconnected;
  const Extctrls::TImage * const mImageUnselectedConnected;
  const Extctrls::TImage * const mImageSelectedConnected;

  private:
  bool mSelected;
  Extctrls::TImage * const mImage;
  TFormMachine * const mBelongsTo;
  ConnectorControl * mIsConnectedTo;
  void UpdateImage();
};
//---------------------------------------------------------------------------
struct CinchRedFemaleControl : public ConnectorControl
{
  CinchRedFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<CinchRedFemale> cinchFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<CinchRedFemale> mCinchFemale;

  //CinchRedFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~CinchRedFemaleControl() {}
  friend boost::checked_delete(CinchRedFemaleControl*);
};
//---------------------------------------------------------------------------
struct CinchWhiteFemaleControl : public ConnectorControl
{
  CinchWhiteFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<CinchWhiteFemale> cinchFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<CinchWhiteFemale> mCinchFemale;

  //CinchWhiteFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~CinchWhiteFemaleControl() {}
  friend boost::checked_delete(CinchWhiteFemaleControl*);
};
//---------------------------------------------------------------------------
struct CinchRedMaleControl : public ConnectorControl
{
  CinchRedMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<CinchRedMale> cinchMale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<CinchRedMale> mCinchMale;

  //CinchRedMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~CinchRedMaleControl() {}
  friend boost::checked_delete(CinchRedMaleControl*);
};
//---------------------------------------------------------------------------
struct CinchWhiteMaleControl : public ConnectorControl
{
  CinchWhiteMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<CinchRedMale> cinchMale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<CinchRedMale> mCinchMale;

  //CinchWhiteMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~CinchWhiteMaleControl() {}
  friend boost::checked_delete(CinchWhiteMaleControl*);
};
//---------------------------------------------------------------------------
struct DmxFemaleControl : public ConnectorControl
{
  DmxFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<DmxFemale> dmxFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<DmxFemale> mDmxFemale;

  //DmxFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~DmxFemaleControl() {}
  friend boost::checked_delete(DmxFemaleControl*);
};
//---------------------------------------------------------------------------
struct DmxMaleControl : public ConnectorControl
{
  DmxMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<DmxMale> dmxMale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<DmxMale> mDmxMale;

  //DmxMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~DmxMaleControl() {}
  friend boost::checked_delete(DmxMaleControl*);
};
//---------------------------------------------------------------------------
struct EuroFemaleControl : public ConnectorControl
{
  EuroFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<EuroFemale> euroFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<EuroFemale> mEuroFemale;

  //EuroFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~EuroFemaleControl() {}
  friend boost::checked_delete(EuroFemaleControl*);
};
//---------------------------------------------------------------------------
struct EuroMaleControl : public ConnectorControl
{
  EuroMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<EuroMale> euroMale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<EuroMale> mEuroMale;

  //EuroMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~EuroMaleControl() {}
  friend boost::checked_delete(EuroMaleControl*);
};
//---------------------------------------------------------------------------
struct JackFemaleControl : public ConnectorControl
{
  JackFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<JackFemale> euroFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<JackFemale> mJackFemale;

  //JackFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~JackFemaleControl() {}
  friend boost::checked_delete(JackFemaleControl*);
};
//---------------------------------------------------------------------------
struct JackXlrFemaleControl : public ConnectorControl
{
  JackXlrFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<JackXlrFemale> euroFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<JackXlrFemale> mJackXlrFemale;

  //JackXlrFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~JackXlrFemaleControl() {}
  friend boost::checked_delete(JackXlrFemaleControl*);
};
//---------------------------------------------------------------------------
struct JackMaleControl : public ConnectorControl
{
  JackMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<JackMale> euroFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<JackMale> mJackMale;

  //JackMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~JackMaleControl() {}
  friend boost::checked_delete(JackMaleControl*);
};
//---------------------------------------------------------------------------
struct Plug220Control : public ConnectorControl
{
  Plug220Control(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<Plug220> plug220,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<Plug220> mPlug220;

  //Plug220Control can only be deleted by boost::shared_ptr
  //or its descendants
  ~Plug220Control() {}
  friend boost::checked_delete(Plug220Control*);
};
//---------------------------------------------------------------------------
struct Socket220Control : public ConnectorControl
{
  Socket220Control(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<Socket220> socket220,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();


  private:

  boost::shared_ptr<Socket220> mSocket220;

  //Socket220Control can only be deleted by boost::shared_ptr
  //or its descendants
  ~Socket220Control() {}
  friend boost::checked_delete(Socket220Control*);
};
//---------------------------------------------------------------------------
struct SocketPowerFemaleControl : public ConnectorControl
{
  SocketPowerFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<SocketPowerFemale> socketPowerFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();


  private:

  boost::shared_ptr<SocketPowerFemale> mSocketPowerFemale;

  //SocketPowerFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~SocketPowerFemaleControl() {}
  friend boost::checked_delete(SocketPowerFemaleControl*);
};
//---------------------------------------------------------------------------
struct SocketPowerMaleControl : public ConnectorControl
{
  SocketPowerMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<SocketPowerMale> socketPowerMale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();


  private:

  boost::shared_ptr<SocketPowerMale> mSocketPowerMale;

  //SocketPowerMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~SocketPowerMaleControl() {}
  friend boost::checked_delete(SocketPowerMaleControl*);
};
//---------------------------------------------------------------------------
struct SpeakonFemaleControl : public ConnectorControl
{
  SpeakonFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<SpeakonFemale> euroFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<SpeakonFemale> mSpeakonFemale;

  //SpeakonFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~SpeakonFemaleControl() {}
  friend boost::checked_delete(SpeakonFemaleControl*);
};
//---------------------------------------------------------------------------
struct SpeakonMaleControl : public ConnectorControl
{
  SpeakonMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<SpeakonMale> euroFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<SpeakonMale> mSpeakonMale;

  //SpeakonMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~SpeakonMaleControl() {}
  friend boost::checked_delete(SpeakonMaleControl*);
};
//---------------------------------------------------------------------------
struct XlrFemaleControl : public ConnectorControl
{
  XlrFemaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<XlrFemale> xlrFemale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<XlrFemale> mXlrFemale;

  //XlrFemaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~XlrFemaleControl() {}
  friend boost::checked_delete(XlrFemaleControl*);
};
//---------------------------------------------------------------------------
struct XlrMaleControl : public ConnectorControl
{
  XlrMaleControl(
    TFormMachine * const belongsTo,
    const boost::shared_ptr<XlrMale> xlrMale,
    Extctrls::TImage * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  boost::shared_ptr<XlrMale> mXlrMale;

  //XlrMaleControl can only be deleted by boost::shared_ptr
  //or its descendants
  ~XlrMaleControl() {}
  friend boost::checked_delete(XlrMaleControl*);
};
//---------------------------------------------------------------------------



#endif
