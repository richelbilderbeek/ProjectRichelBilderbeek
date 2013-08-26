//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include <cassert>
#include <boost/scoped_ptr.hpp>
#include "UnitConnector.h"
#include "UnitConnectorControl.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
//---------------------------------------------------------------------------
ConnectorControl::ConnectorControl(TFormMachine * const belongsTo,
  Extctrls::TImage * const image,
  const Extctrls::TImage * const imageUnselectedUnconnected,
  const Extctrls::TImage * const imageSelectedUnconnected,
  const Extctrls::TImage * const imageUnselectedConnected,
  const Extctrls::TImage * const imageSelectedConnected)
  : mBelongsTo(belongsTo),
    mImage(image),
    mImageUnselectedUnconnected(imageUnselectedUnconnected),
    mImageSelectedUnconnected(imageSelectedUnconnected),
    mImageUnselectedConnected(imageUnselectedConnected),
    mImageSelectedConnected(imageSelectedConnected),
    mSelected(false),
    mIsConnectedTo(0)
{
  assert(mBelongsTo != 0);
  assert(mImage != 0);
}
//---------------------------------------------------------------------------
void ConnectorControl::Select()
{
  mSelected = true;
  this->UpdateImage();
}
//---------------------------------------------------------------------------
void ConnectorControl::Unselect()
{
  mSelected = false;
  this->UpdateImage();
}
//---------------------------------------------------------------------------
const bool ConnectorControl::CanConnect(
  ConnectorControl * const otherConnectorControl) const
{
  assert(otherConnectorControl != 0);

  //Two ConnectorControls can connect if their Connectors can connect
  const Connector * const thisConnector = this->GetConnector();
  const Connector * const otherConnector = otherConnectorControl->GetConnector();

  assert(thisConnector  != 0);
  assert(otherConnector != 0);

  assert ( thisConnector->CanConnect(otherConnector)
      == otherConnector->CanConnect(thisConnector)
    && "If A can (not) connect to B, B can (not) connect to A");

  return thisConnector->CanConnect(otherConnector);
}
//---------------------------------------------------------------------------
void ConnectorControl::Connect(ConnectorControl * const otherConnectorControl)
{
  assert(otherConnectorControl != 0);
  assert(this->CanConnect(otherConnectorControl)==true);

  {
    //Connect the two ConnectorControls
    this->mIsConnectedTo = otherConnectorControl;
    otherConnectorControl->mIsConnectedTo = this; //???Should not compile???
    assert(this->IsConnected() == true);
    assert(otherConnectorControl->IsConnected() == true);
  }

  {
    //Connect the two Connectors the ConnectorControls manage
    Connector * const thisConnector = this->GetConnector();
    assert(thisConnector != 0);
    Connector * const otherConnector = otherConnectorControl->GetConnector();
    assert(otherConnector != 0);

    //Two connections will take place, therefore otherConnector is either
    //null or already connected to this connector
    assert( (thisConnector->GetConnectedTo() == 0
        || thisConnector->GetConnectedTo() == otherConnector)
      && "Assume not connected and that this is handled by GUI?");
    assert( (otherConnector->GetConnectedTo() == 0
        || otherConnector->GetConnectedTo() == thisConnector)
      && "Assume not connected and that this is handled by GUI?");
    //Connect
    thisConnector->Connect(otherConnector);
    otherConnector->Connect(thisConnector);

    assert(thisConnector->IsConnected() == true);
    assert(otherConnector->IsConnected() == true);
  }

  //Choose image
  this->UpdateImage();
}
//---------------------------------------------------------------------------
const bool ConnectorControl::IsConnected() const
{
  return (this->mIsConnectedTo != 0);
}
//---------------------------------------------------------------------------
const bool ConnectorControl::IsConnectedTo(const ConnectorControl * other) const
{
  return (this->mIsConnectedTo == other);
}
//---------------------------------------------------------------------------
void ConnectorControl::Disconnect()
{
  //Disconnect the ConnectorControl
  mIsConnectedTo = 0;

  //Disconnect the Connector
  this->GetConnector()->Disconnect();

  this->UpdateImage();
}
//---------------------------------------------------------------------------
void ConnectorControl::UpdateImage()
{
  if (mSelected == true)
  {
    if (this->IsConnected() == true)
    {
      mImage->Picture = mImageSelectedConnected->Picture;
    }
    else
    {
      mImage->Picture = mImageSelectedUnconnected->Picture;
    }
  }
  else
  {
    if (this->IsConnected() == true)
    {
      mImage->Picture = mImageUnselectedConnected->Picture;
    }
    else
    {
      mImage->Picture = mImageUnselectedUnconnected->Picture;
    }
  }
}
//---------------------------------------------------------------------------
CinchRedFemaleControl::CinchRedFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<CinchRedFemale> cinchFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(
      belongsTo,
      image,
      FormSprites->ImageCinchFemaleRed,
      FormSprites->ImageCinchFemaleRedSelected,
      FormSprites->ImageCinchFemaleRedConnected,
      FormSprites->ImageCinchFemaleRedConnectedSelected),
    mCinchFemale(cinchFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const CinchRedFemaleControl::GetConnector() const
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
Connector * CinchRedFemaleControl::GetConnector()
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
CinchWhiteFemaleControl::CinchWhiteFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<CinchWhiteFemale> cinchFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(
      belongsTo,
      image,
      FormSprites->ImageCinchFemaleWhite,
      FormSprites->ImageCinchFemaleWhiteSelected,
      FormSprites->ImageCinchFemaleWhiteConnected,
      FormSprites->ImageCinchFemaleWhiteConnectedSelected),
    mCinchFemale(cinchFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const CinchWhiteFemaleControl::GetConnector() const
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
Connector * CinchWhiteFemaleControl::GetConnector()
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
DmxFemaleControl::DmxFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<DmxFemale> dmxFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(
      belongsTo,
      image,
      FormSprites->ImageDmxFemale,
      FormSprites->ImageDmxFemaleSelected,
      FormSprites->ImageDmxFemaleConnected,
      FormSprites->ImageDmxFemaleConnectedSelected),
    mDmxFemale(dmxFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const DmxFemaleControl::GetConnector() const
{
  return mDmxFemale.get();
}
//---------------------------------------------------------------------------
Connector * DmxFemaleControl::GetConnector()
{
  return mDmxFemale.get();
}
//---------------------------------------------------------------------------
DmxMaleControl::DmxMaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<DmxMale> euroMale,
  Extctrls::TImage * const image)
  : ConnectorControl(
      belongsTo,
      image,
      FormSprites->ImageDmxMale,
      FormSprites->ImageDmxMaleSelected,
      FormSprites->ImageDmxMaleConnected,
      FormSprites->ImageDmxMaleConnectedSelected),
    mDmxMale(euroMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const DmxMaleControl::GetConnector() const
{
  return mDmxMale.get();
}
//---------------------------------------------------------------------------
Connector * DmxMaleControl::GetConnector()
{
  return mDmxMale.get();
}
//---------------------------------------------------------------------------
EuroMaleControl::EuroMaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<EuroMale> euroMale,
  Extctrls::TImage * const image)
  : ConnectorControl(
      belongsTo,
      image,
      FormSprites->ImageEuroMale,
      FormSprites->ImageEuroMaleSelected,
      FormSprites->ImageEuroMaleConnected,
      FormSprites->ImageEuroMaleConnectedSelected),
    mEuroMale(euroMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const EuroMaleControl::GetConnector() const
{
  return mEuroMale.get();
}
//---------------------------------------------------------------------------
Connector * EuroMaleControl::GetConnector()
{
  return mEuroMale.get();
}
//---------------------------------------------------------------------------
EuroFemaleControl::EuroFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<EuroFemale> euroMale,
  Extctrls::TImage * const image)
  : ConnectorControl(
      belongsTo,
      image,
      FormSprites->ImageEuroFemale,
      FormSprites->ImageEuroFemaleSelected,
      FormSprites->ImageEuroFemaleConnected,
      FormSprites->ImageEuroFemaleConnectedSelected),
    mEuroFemale(euroMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const EuroFemaleControl::GetConnector() const
{
  return mEuroFemale.get();
}
//---------------------------------------------------------------------------
Connector * EuroFemaleControl::GetConnector()
{
  return mEuroFemale.get();
}
//---------------------------------------------------------------------------
JackFemaleControl::JackFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<JackFemale> xlrFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageJackFemale,
      FormSprites->ImageJackFemaleSelected,
      FormSprites->ImageJackFemaleConnected,
      FormSprites->ImageJackFemaleConnectedSelected),
    mJackFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const JackFemaleControl::GetConnector() const
{
  return mJackFemale.get();
}
//---------------------------------------------------------------------------
Connector * JackFemaleControl::GetConnector()
{
  return mJackFemale.get();
}
//---------------------------------------------------------------------------
JackXlrFemaleControl::JackXlrFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<JackXlrFemale> xlrFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageJackXlrFemale,
      FormSprites->ImageJackXlrFemaleSelected,
      FormSprites->ImageJackXlrFemaleConnected,
      FormSprites->ImageJackXlrFemaleConnectedSelected),
    mJackXlrFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const JackXlrFemaleControl::GetConnector() const
{
  return mJackXlrFemale.get();
}
//---------------------------------------------------------------------------
Connector * JackXlrFemaleControl::GetConnector()
{
  return mJackXlrFemale.get();
}
//---------------------------------------------------------------------------
JackMaleControl::JackMaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<JackMale> xlrFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageJackMale,
      FormSprites->ImageJackMaleSelected,
      FormSprites->ImageJackMaleConnected,
      FormSprites->ImageJackMaleConnectedSelected),
    mJackMale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const JackMaleControl::GetConnector() const
{
  return mJackMale.get();
}
//---------------------------------------------------------------------------
Connector * JackMaleControl::GetConnector()
{
  return mJackMale.get();
}
//---------------------------------------------------------------------------
Plug220Control::Plug220Control(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<Plug220> plug220,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImagePlug220,
      FormSprites->ImagePlug220Selected,
      FormSprites->ImagePlug220Connected,
      FormSprites->ImagePlug220ConnectedSelected),
    mPlug220(plug220)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const Plug220Control::GetConnector() const
{
  return mPlug220.get();
}
//---------------------------------------------------------------------------
Connector * Plug220Control::GetConnector()
{
  return mPlug220.get();
}
//---------------------------------------------------------------------------
Socket220Control::Socket220Control(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<Socket220> socket220,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageSocket220,
      FormSprites->ImageSocket220Selected,
      FormSprites->ImageSocket220Connected,
      FormSprites->ImageSocket220ConnectedSelected),
    mSocket220(socket220)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const Socket220Control::GetConnector() const
{
  return mSocket220.get();
}
//---------------------------------------------------------------------------
Connector * Socket220Control::GetConnector()
{
  return mSocket220.get();
}
//---------------------------------------------------------------------------
SocketPowerFemaleControl::SocketPowerFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<SocketPowerFemale> socketPowerFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageSocketPowerFemale,
      FormSprites->ImageSocketPowerFemaleSelected,
      FormSprites->ImageSocketPowerFemaleConnected,
      FormSprites->ImageSocketPowerFemaleConnectedSelected),
    mSocketPowerFemale(socketPowerFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SocketPowerFemaleControl::GetConnector() const
{
  return mSocketPowerFemale.get();
}
//---------------------------------------------------------------------------
Connector * SocketPowerFemaleControl::GetConnector()
{
  return mSocketPowerFemale.get();
}
//---------------------------------------------------------------------------
SocketPowerMaleControl::SocketPowerMaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<SocketPowerMale> socketPowerMale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageSocketPowerMale,
      FormSprites->ImageSocketPowerMaleSelected,
      FormSprites->ImageSocketPowerMaleConnected,
      FormSprites->ImageSocketPowerMaleConnectedSelected),
    mSocketPowerMale(socketPowerMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SocketPowerMaleControl::GetConnector() const
{
  return mSocketPowerMale.get();
}
//---------------------------------------------------------------------------
Connector * SocketPowerMaleControl::GetConnector()
{
  return mSocketPowerMale.get();
}
//---------------------------------------------------------------------------
SpeakonFemaleControl::SpeakonFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<SpeakonFemale> xlrFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageSpeakonFemale,
      FormSprites->ImageSpeakonFemaleSelected,
      FormSprites->ImageSpeakonFemaleConnected,
      FormSprites->ImageSpeakonFemaleConnectedSelected),
    mSpeakonFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SpeakonFemaleControl::GetConnector() const
{
  return mSpeakonFemale.get();
}
//---------------------------------------------------------------------------
Connector * SpeakonFemaleControl::GetConnector()
{
  return mSpeakonFemale.get();
}
//---------------------------------------------------------------------------
SpeakonMaleControl::SpeakonMaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<SpeakonMale> xlrFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageSpeakonMale,
      FormSprites->ImageSpeakonMaleSelected,
      FormSprites->ImageSpeakonMaleConnected,
      FormSprites->ImageSpeakonMaleConnectedSelected),
    mSpeakonMale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SpeakonMaleControl::GetConnector() const
{
  return mSpeakonMale.get();
}
//---------------------------------------------------------------------------
Connector * SpeakonMaleControl::GetConnector()
{
  return mSpeakonMale.get();
}
//---------------------------------------------------------------------------
XlrFemaleControl::XlrFemaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<XlrFemale> xlrFemale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageXlrFemale,
      FormSprites->ImageXlrFemaleSelected,
      FormSprites->ImageXlrFemaleConnected,
      FormSprites->ImageXlrFemaleConnectedSelected),
    mXlrFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const XlrFemaleControl::GetConnector() const
{
  return mXlrFemale.get();
}
//---------------------------------------------------------------------------
Connector * XlrFemaleControl::GetConnector()
{
  return mXlrFemale.get();
}
//---------------------------------------------------------------------------
XlrMaleControl::XlrMaleControl(
  TFormMachine * const belongsTo,
  const boost::shared_ptr<XlrMale> xlrMale,
  Extctrls::TImage * const image)
  : ConnectorControl(belongsTo,image,
      FormSprites->ImageXlrMale,
      FormSprites->ImageXlrMaleSelected,
      FormSprites->ImageXlrMaleConnected,
      FormSprites->ImageXlrMaleConnectedSelected),
    mXlrMale(xlrMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const XlrMaleControl::GetConnector() const
{
  return mXlrMale.get();
}
//---------------------------------------------------------------------------
Connector * XlrMaleControl::GetConnector()
{
  return mXlrMale.get();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

