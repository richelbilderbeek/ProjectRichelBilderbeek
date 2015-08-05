#include <cassert>

#include <boost/signals2.hpp>

#include "emitter.h"
#include "receiver.h"

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

    //Create the emitter and receiver
    Emitter e;
    Receiver r;

    //The emitter is not yet connected to a receiver/slot
    assert(e.m_signal.num_slots() == 0);

    //Connect the emitter to a receiver/slot
    e.m_signal.connect(
      boost::bind(
        &Receiver::OnReceive,r //Don't forget to put placeholders here (e.g. _1 ) if the signal have additional arguments
      )
    );

    //The emitter is now connected to a receiver/slot
    assert(e.m_signal.num_slots() == 1);

    //Make the magic happen: the emitter puts out a signal and -unknown to it- the receiver responds
    e.DoEmit();
  }
  assert(1==2);
}
