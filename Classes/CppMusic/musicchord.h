#ifndef MUSICCHORD_H
#define MUSICCHORD_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "musicnote.h"

namespace ribi {

namespace Music {

struct Chord
{

  ///Create any Chord from its root (e.g. 'C'), postfix (e.g. 'm7') and its intervals
  explicit Chord(
    const Note root,
    const std::string& postfix,
    const std::vector<int>& intervals);

  virtual ~Chord() {}

  ///Count the number of notes two chords share
  static int CountSameNotes(const boost::shared_ptr<Chord>& lhs, const boost::shared_ptr<Chord>& rhs);

  ///A Factory method: create all Chords
  static std::vector<boost::shared_ptr<Chord> > CreateAllChords();

  ///A Factory method: create all Chords from a root
  static std::vector<boost::shared_ptr<Chord> > CreateChords(const Note root);

  ///A Factory method: create a Chord from its name (which includes its root)
  static boost::shared_ptr<Chord> CreateChord(const std::string& chord_name);

  ///Obtain the Chord its name
  ///For example, 'C' (for C major) or 'D#m'
  virtual const std::string GetName() const = 0;

  ///Obtain a Chord its Notes
  ///For example, the chord C major will returnn {C,E,G}
  const std::vector<Note> GetNotes() const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Test this class
  static void Test();

  ///Return the Chord as a music notation string
  const std::string ToStr() const;

  private:

  ///The root of a chord. For example, the Cm7 chord has C as its root
  Note m_root;

  ///The postfix of a chord. For example, the Cm7 chord has 'm7' as its postfix
  const std::string m_postfix;

  const std::vector<int> m_intervals;
};

///The aug or plus chord
///For example, 'C+', 'D#aug"
struct ChordAug : public Chord
{
  ///Create the Chord from its root
  ChordAug(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "aug"; }
};

///The dim chord
///For example, 'Cdim', 'D#dim"
struct ChordDim : public Chord
{
  ///Create the Chord from its root
  ChordDim(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "dim"; }
};

///The major chord
///For example, 'C', 'D#"
struct ChordMajor : public Chord
{
  ///Create the Chords from its root
  ChordMajor(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "major"; }
};

///The minor chord
///For example, 'Cm', 'D#m"
struct ChordMinor : public Chord
{
  ///Create the Chord from its root
  ChordMinor(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "minor"; }
};

///The 6 chord
///For example, 'C6', 'D#6"
struct Chord6 : public Chord
{
  ///Create the Chord from its root
  Chord6(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "6"; }
};

///The minor 6 chord
///For example, 'Cm6', 'D#m6"
struct ChordMinor6 : public Chord
{
  ///Create the Chord from its root
  ChordMinor6(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "m6"; }
};

///The 7 chord
///For example, 'C7', 'D#7"
struct Chord7 : public Chord
{
  ///Create the Chord from its root
  Chord7(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "7"; }
};

///The minor 7 chord
///For example, 'C7', 'D#7"
struct ChordMinor7 : public Chord
{
  ///Create the Chord from its root
  ChordMinor7(const Note root);

  ///Obtain the Scale its name
  const std::string GetName() const { return "m7"; }
};

} //~namespace Music

} //~namespace ribi

#endif // MUSICCHORD_H
