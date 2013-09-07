#ifndef MIDILESSONCREATORMAINDIALOG_H
#define MIDILESSONCREATORMAINDIALOG_H

#include <string>

namespace ribi {

///Creates the Midi files as if from command line
struct MidiLessonCreatorMainDialog
{
  ///Create a lesson and write it to a MIDI file
  static void CreateLesson(const int level, const std::string& midi_filename);

  private:
};

} //~namespace ribi

#endif // MIDILESSONCREATORMAINDIALOG_H
