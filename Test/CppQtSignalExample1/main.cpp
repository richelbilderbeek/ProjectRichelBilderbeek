#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "emitter.h"
#include "receiver.h"
#pragma GCC diagnostic pop

int main()
{
  const Emitter e;
  const Receiver r;
  QObject::connect(&e,SIGNAL(signal_emit()),&r,SLOT(OnReceive()));
  e.DoEmit();
}

/* Screen output:

Emitter: emitting signal
Receiver: received signal

*/
