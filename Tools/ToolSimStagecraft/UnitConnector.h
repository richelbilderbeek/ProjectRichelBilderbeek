//---------------------------------------------------------------------------

#ifndef UnitConnectorH
#define UnitConnectorH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "UnitMachine.h"
//---------------------------------------------------------------------------
// Every Machine has at least one Connector
// A Connector belongs to a Machine and is of a certain type
struct Connector
{
  Connector(const Machine * const belongsTo);

  void Connect(const Connector * const otherConnector);
  void Disconnect();
  const Connector * const GetConnectedTo() const;

  virtual const bool CanConnect(
    const Connector * const otherConnector) const = 0;

  const Machine * const mBelongsTo;
  const bool IsConnected() const { return (mConnectedTo!=0); }

  protected:
  //Connector can only be deleted by boost::shared_ptr
  //or descendants
  virtual ~Connector() {}
  friend boost::checked_delete(Connector *);


  private:
  const Connector * mConnectedTo;

};
//---------------------------------------------------------------------------
struct CinchRedFemale : public Connector
{
  CinchRedFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //CinchRedFemale can only be deleted by boost::shared_ptr
  ~CinchRedFemale() {}
  friend boost::checked_delete(CinchRedFemale *);

};
//---------------------------------------------------------------------------
struct CinchRedMale : public Connector
{
  CinchRedMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //CinchRedMale can only be deleted by boost::shared_ptr
  ~CinchRedMale() {}
  friend boost::checked_delete(CinchRedMale *);

};
//---------------------------------------------------------------------------
struct CinchWhiteFemale : public Connector
{
  CinchWhiteFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //CinchWhiteFemale can only be deleted by boost::shared_ptr
  ~CinchWhiteFemale() {}
  friend boost::checked_delete(CinchWhiteFemale *);

};
//---------------------------------------------------------------------------
struct CinchWhiteMale : public Connector
{
  CinchWhiteMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //CinchWhiteMale can only be deleted by boost::shared_ptr
  ~CinchWhiteMale() {}
  friend boost::checked_delete(CinchWhiteMale *);

};
//---------------------------------------------------------------------------
struct DmxFemale : public Connector
{
  DmxFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //DmxFemale can only be deleted by boost::shared_ptr
  ~DmxFemale() {}
  friend boost::checked_delete(DmxFemale *);

};
//---------------------------------------------------------------------------
struct DmxMale : public Connector
{
  DmxMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //DmxMale can only be deleted by boost::shared_ptr
  ~DmxMale() {}
  friend boost::checked_delete(DmxMale *);

};
//---------------------------------------------------------------------------
struct EuroFemale : public Connector
{
  EuroFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //EuroFemale can only be deleted by boost::shared_ptr
  ~EuroFemale() {}
  friend boost::checked_delete(EuroFemale *);

};
//---------------------------------------------------------------------------
struct EuroMale : public Connector
{
  EuroMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //EuroMale can only be deleted by boost::shared_ptr
  ~EuroMale() {}
  friend boost::checked_delete(EuroMale *);

};
//---------------------------------------------------------------------------
// InternalConnection is a soldered connection internal to a machine
// For example, the connection between a power LED and a triplet
struct InternalConnection : public Connector
{
  InternalConnection(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //InternalConnection can only be deleted by boost::shared_ptr
  ~InternalConnection() {}
  friend boost::checked_delete(InternalConnection *);

};
//---------------------------------------------------------------------------
struct JackFemale : public Connector
{
  JackFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //JackFemale can only be deleted by boost::shared_ptr
  ~JackFemale() {}
  friend boost::checked_delete(JackFemale *);

};
//---------------------------------------------------------------------------
//Combo connector of both jack female and XLR female
struct JackXlrFemale : public Connector
{
  JackXlrFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //JackXlrFemale can only be deleted by boost::shared_ptr
  ~JackXlrFemale() {}
  friend boost::checked_delete(JackXlrFemale *);

};
//---------------------------------------------------------------------------
struct JackMale : public Connector
{
  JackMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //JackMale can only be deleted by boost::shared_ptr
  ~JackMale() {}
  friend boost::checked_delete(JackMale *);
};
//---------------------------------------------------------------------------
struct Plug220 : public Connector
{
  Plug220(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //Plug220 can only be deleted by boost::shared_ptr
  ~Plug220() {}
  friend boost::checked_delete(Plug220 *);

};
//---------------------------------------------------------------------------
struct SpeakonFemale : public Connector
{
  SpeakonFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //SpeakonFemale can only be deleted by boost::shared_ptr
  ~SpeakonFemale() {}
  friend boost::checked_delete(SpeakonFemale *);

};
//---------------------------------------------------------------------------
struct SpeakonMale : public Connector
{
  SpeakonMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //SpeakonMale can only be deleted by boost::shared_ptr
  ~SpeakonMale() {}
  friend boost::checked_delete(SpeakonMale *);
};
//---------------------------------------------------------------------------
struct SocketPowerMale : public Connector
{
  SocketPowerMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //SocketPowerMale can only be deleted by boost::shared_ptr
  ~SocketPowerMale() {}
  friend boost::checked_delete(SocketPowerMale *);

};
//---------------------------------------------------------------------------
struct Socket220 : public Connector
{
  Socket220(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //Socket220 can only be deleted by boost::shared_ptr
  ~Socket220() {}
  friend boost::checked_delete(Socket220 *);

};
//---------------------------------------------------------------------------
struct SocketPowerFemale : public Connector
{
  SocketPowerFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //SocketPowerFemale can only be deleted by boost::shared_ptr
  ~SocketPowerFemale() {}
  friend boost::checked_delete(SocketPowerFemale *);
};
//---------------------------------------------------------------------------
struct XlrFemale : public Connector
{
  XlrFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //XlrFemale can only be deleted by boost::shared_ptr
  ~XlrFemale() {}
  friend boost::checked_delete(XlrFemale *);

};
//---------------------------------------------------------------------------
struct XlrMale : public Connector
{
  XlrMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  //XlrMale can only be deleted by boost::shared_ptr
  ~XlrMale() {}
  friend boost::checked_delete(XlrMale *);

};
//---------------------------------------------------------------------------
#endif
