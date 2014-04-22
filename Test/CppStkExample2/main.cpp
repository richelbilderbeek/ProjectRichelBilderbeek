
//From http://www.richelbilderbeek.nl/CppStk.htm
//Modified from crtsine.cpp STK tutorial program
#include <boost/static_assert.hpp>
#include <boost/timer.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include "SineWave.h"
#include "RtAudio.h"
#pragma GCC diagnostic pop

// This tick() function handles sample computation only. It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick(
  void *outputBuffer, void * /*inputBuffer*/,
  unsigned int nBufferFrames,
  double /*streamTime*/, RtAudioStreamStatus /*status*/,
  void *dataPointer)
{
  stk::SineWave * const sine = (stk::SineWave *) dataPointer;
  stk::StkFloat * samples = (stk::StkFloat *) outputBuffer;

  for ( unsigned int i=0; i!=nBufferFrames; ++i )
    *samples++ = sine->tick();
  return 0;
}


int main()
{
  // Set the global sample rate before creating class instances.
  stk::Stk::setSampleRate( 44100.0 );

  // Setup the RtAudio stream.
  RtAudio dac;
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 1;
  BOOST_STATIC_ASSERT(sizeof(stk::StkFloat) == 8);
  unsigned int bufferFrames = stk::RT_BUFFER_SIZE;

  while (1)
  {
    //Choose a random beep frequency
    stk::SineWave sine;
    dac.openStream(
      &parameters, NULL,
      RTAUDIO_FLOAT64,
      (unsigned int)stk::Stk::sampleRate(),
      &bufferFrames, &tick,
      (void *)&sine );
    sine.setFrequency(100.0
      + static_cast<double>(std::rand()%1000));
    dac.startStream();
    //Let it beep for 0.2 seconds
    boost::timer t;
    while (t.elapsed() < 0.2 ) {}
    //Prepare for next beep
    dac.closeStream();
  }
}

