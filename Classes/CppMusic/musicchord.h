#ifndef MUSICCHORD_H
#define MUSICCHORD_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "musicnote.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace Music {

struct Chord
{

  ///Create any Chord from its root (e.g. 'C'), postfix (e.g. 'm7') and its intervals
  explicit Chord(
    const Note root,
    const std::string& postfix,
    const std::vector<int>& intervals);

  virtual ~Chord() noexcept {}

  ///Count the number of notes two chords share
  static int CountSameNotes(const boost::shared_ptr<Chord>& lhs, const boost::shared_ptr<Chord>& rhs);

  ///A Factory method: create all Chords
  static std::vector<boost::shared_ptr<Chord> > CreateAllChords() noexcept;

  ///A Factory method: create all Chords from a root
  static std::vector<boost::shared_ptr<Chord> > CreateChords(const Note root) noexcept;

  ///A Factory method: create a Chord from its name (which includes its root)
  static boost::shared_ptr<Chord> CreateChord(const std::string& chord_name) noexcept;

  ///Obtain the Chord its name
  ///For example, 'C' (for C major) or 'D#m'
  virtual std::string GetName() const noexcept = 0;

  ///Obtain a Chord its Notes
  ///For example, the chord C major will returnn {C,E,G}
  const std::vector<Note> GetNotes() const noexcept;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Test this class
  static void Test() noexcept;

  ///Return the Chord as a music notation string
  std::string ToStr() const noexcept;

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
  ChordAug(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "aug"; }
};

///The dim chord
///For example, 'Cdim', 'D#dim"
struct ChordDim : public Chord
{
  ///Create the Chord from its root
  ChordDim(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "dim"; }
};

///The major chord
///For example, 'C', 'D#"
struct ChordMajor : public Chord
{
  ///Create the Chords from its root
  ChordMajor(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "major"; }
};

///The minor chord
///For example, 'Cm', 'D#m"
struct ChordMinor : public Chord
{
  ///Create the Chord from its root
  ChordMinor(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "minor"; }
};

///The 6 chord
///For example, 'C6', 'D#6"
struct Chord6 : public Chord
{
  ///Create the Chord from its root
  Chord6(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "6"; }
};

///The minor 6 chord
///For example, 'Cm6', 'D#m6"
struct ChordMinor6 : public Chord
{
  ///Create the Chord from its root
  ChordMinor6(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "m6"; }
};

///The 7 chord
///For example, 'C7', 'D#7"
struct Chord7 : public Chord
{
  ///Create the Chord from its root
  Chord7(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "7"; }
};

///The minor 7 chord
///For example, 'C7', 'D#7"
struct ChordMinor7 : public Chord
{
  ///Create the Chord from its root
  ChordMinor7(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "m7"; }
};

} //~namespace Music

} //~namespace ribi

#endif // MUSICCHORD_H
