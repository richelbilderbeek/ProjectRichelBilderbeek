#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>

#include "emitter.h"
#include "receiver.h"
#pragma GCC diagnostic pop

int main()
{
  {
    //The Qt way
    QtEmitter e;
    QtReceiver r;
    QObject::connect(&e,SIGNAL(signal_emit()),&r,SLOT(OnReceive()));
    e.DoEmit();
  }
  {
    //The Boost way
    Emitter e;
    Receiver r;
    e.m_signal.connect(
      boost::bind(
        &Receiver::OnReceive,
        r));
    e.DoEmit();
  }
}
