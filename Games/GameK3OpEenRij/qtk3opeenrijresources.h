#ifndef QTK3OPEENRIJRESOURCES_H
#define QTK3OPEENRIJRESOURCES_H

#include "connectthreeresources.h"

///QtK3OpEenRijResources is a class containing
///all filenames to be used by the program
///Its base class, ConnectThreeResources,
///ensures the files needed are present upon construction.
struct QtK3OpEenRijResources
  : public ConnectThreeResources
{
  QtK3OpEenRijResources();
};

#endif // QTK3OPEENRIJRESOURCES_H
