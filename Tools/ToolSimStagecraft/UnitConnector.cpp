//---------------------------------------------------------------------------
#include <vcl.h> //For precompiled header
#pragma hdrstop

#include "UnitConnector.h"

//---------------------------------------------------------------------------
Connector::Connector(const Machine * const belongsTo)
  : mBelongsTo(belongsTo), mConnectedTo(0)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
void Connector::Connect(const Connector * const otherConnector)
{
  assert(otherConnector != 0);
  assert( (mConnectedTo == 0
    || mConnectedTo == otherConnector)
  && "Assume GUI handles this");

  //Two connections will take place, therefore otherConnector is either
  //null or already connected to this connector
  assert( (otherConnector->GetConnectedTo() == 0
    || otherConnector->GetConnectedTo() == this)
    && "Assume GUI handles this");

  if (this->CanConnect(otherConnector)==true)
  {
    mConnectedTo = otherConnector;
  }
}
//---------------------------------------------------------------------------
void Connector::Disconnect()
{
  mConnectedTo = 0;
}
//---------------------------------------------------------------------------
const Connector * const Connector::GetConnectedTo() const
{
  return mConnectedTo;
}
//---------------------------------------------------------------------------
const bool CinchRedFemale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const CinchRedFemale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool CinchRedMale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const CinchRedFemale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool CinchWhiteFemale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const CinchWhiteFemale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool CinchWhiteMale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const CinchWhiteFemale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------

const bool DmxFemale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const DmxMale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool DmxMale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const DmxFemale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool EuroFemale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const EuroMale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool EuroMale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const EuroFemale * const>(otherConnector) != 0
    || dynamic_cast<const Socket220* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
// InternalConnection is a soldered connection internal to a machine
// For example, the connection between a power LED and a triplet
const bool InternalConnection::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const InternalConnection* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool JackFemale::CanConnect(const Connector * const otherConnector) const
{
  return (
     dynamic_cast<const JackMale      * const>(otherConnector) != 0
  || dynamic_cast<const JackFemale    * const>(otherConnector) != 0
  || dynamic_cast<const JackXlrFemale * const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool JackXlrFemale::CanConnect(const Connector * const otherConnector) const
{
  return (
     dynamic_cast<const JackMale   * const>(otherConnector) != 0
  || dynamic_cast<const JackFemale * const>(otherConnector) != 0
  || dynamic_cast<const XlrMale    * const>(otherConnector) != 0
  || dynamic_cast<const XlrFemale  * const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool JackMale::CanConnect(const Connector * const otherConnector) const
{
  return (
     dynamic_cast<const JackMale      * const>(otherConnector) != 0
  || dynamic_cast<const JackFemale    * const>(otherConnector) != 0
  || dynamic_cast<const JackXlrFemale * const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool Socket220::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const Plug220 * const>(otherConnector) != 0
    || dynamic_cast<const EuroMale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool SocketPowerFemale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const SocketPowerMale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool Plug220::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const Socket220* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool SocketPowerMale::CanConnect(const Connector * const otherConnector) const
{
  return (dynamic_cast<const SocketPowerFemale* const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool SpeakonFemale::CanConnect(const Connector * const otherConnector) const
{
  return (
     dynamic_cast<const SpeakonMale   * const>(otherConnector) != 0
  || dynamic_cast<const SpeakonFemale * const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool SpeakonMale::CanConnect(const Connector * const otherConnector) const
{
  return (
     dynamic_cast<const SpeakonMale   * const>(otherConnector) != 0
  || dynamic_cast<const SpeakonFemale * const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool XlrFemale::CanConnect(const Connector * const otherConnector) const
{
  return (
    dynamic_cast<const XlrMale       * const>(otherConnector) != 0
 || dynamic_cast<const JackXlrFemale * const>(otherConnector) != 0);
}
//---------------------------------------------------------------------------
const bool XlrMale::CanConnect(const Connector * const otherConnector) const
{
  return (
    dynamic_cast<const XlrFemale* const>(otherConnector) != 0
 || dynamic_cast<const JackXlrFemale * const>(otherConnector) != 0);

}
//---------------------------------------------------------------------------

#pragma package(smart_init)
