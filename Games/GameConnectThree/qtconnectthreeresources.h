#ifndef QTCONNECTTHREERESOURCES_H
#define QTCONNECTTHREERESOURCES_H
//---------------------------------------------------------------------------
#include "connectthreeresources.h"
//---------------------------------------------------------------------------
///QtConnectThreeResources is a Singleton that manages
///all Wt resources. Its base class, ConnectThreeResources,
///ensures the files needed are present upon construction.
struct QtConnectThreeResources
  : public ConnectThreeResources
{
  static QtConnectThreeResources * GetInstance();

  private:
  QtConnectThreeResources() {}
  static QtConnectThreeResources * m_instance;
};
//---------------------------------------------------------------------------
#endif // QTCONNECTTHREERESOURCES_H
