#ifndef MUSICSCALE_H
#define MUSICSCALE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "musicnote.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace Music {

struct Chord;

struct Scale
{
  ///Create a Scale from its root and its intervals
  explicit Scale(const Note root, const std::vector<int>& intervals);

  virtual ~Scale() noexcept {}

  ///A Factory method: create all Scales from a root
  static std::vector<boost::shared_ptr<Scale> > CreateScales(const Note root) noexcept;

  ///A Factory method: create a Scale from its name and root
  static boost::shared_ptr<Scale> CreateScale(
    const std::string& scale_name,
    const Note root);

  ///Does the Chord fit in this Scale?
  bool Fits(const boost::shared_ptr<Chord>& chord) const noexcept;

  ///Obtain the Scale its name
  ///For example, 'Major' or 'Moll-Dur subdominant'
  virtual std::string GetName() const noexcept = 0;

  ///Obtain a Scale its Notes
  ///For example, C major will returnn {A,B,C,D,E,F,G}
  const std::vector<Note> GetNotes() const noexcept;

  const Note& GetRoot() const noexcept { return m_root; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Test this class
  static void Test() noexcept;

  private:
  const Note m_root;

  ///The intervals between two successive notes
  ///For example, the C major scale (notes: C-D-E-F-G-A-B)
  ///has intervals 2-2-1-2-2-2
  ///The sum of the intervals must always be lower than twelve
  const std::vector<int> m_intervals;
};

///The blues scale
struct ScaleBlues : public Scale
{
  ///Create the Scale from its root
  ScaleBlues(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const  noexcept{ return "blues"; }
};

///The harminic minor scale
struct ScaleHarmonicMinor : public Scale
{
  ///Create the Scale from its root
  ScaleHarmonicMinor(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "harmonic minor"; }
};

///The hexatonic scale
struct ScaleHexatonic : public Scale
{
  ///Create the Scale from its root
  ScaleHexatonic(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "hexatonic"; }
};

///The hypermajor scale
struct ScaleHyperMajor : public Scale
{
  ///Create the Scale from its root
  ScaleHyperMajor(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "hypermajor"; }
};

///The major scale
struct ScaleMajor : public Scale
{
  ///Create the Scale from its root
  ScaleMajor(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "major"; }
};

///The major pentatonic scale
struct ScaleMajorPentatonic : public Scale
{
  ///Create the Scale from its root
  ScaleMajorPentatonic(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "major pentatonic"; }
};

///The minor pentatonic scale
struct ScaleMinorPentatonic : public Scale
{
  ///Create the Scale from its root
  ScaleMinorPentatonic(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "minor pentatonic"; }
};

///The Moll-dur dominant scale
struct ScaleMollDurDominant : public Scale
{
  ///Create the Scale from its root
  ScaleMollDurDominant(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "moll-dur dominant"; }
};

///The Moll-dur subdominant scale
struct ScaleMollDurSubdominant : public Scale
{
  ///Create the Scale from its root
  ScaleMollDurSubdominant(const Note root) noexcept;

  ///Obtain the Scale its name
  std::string GetName() const noexcept { return "moll-dur subdominant"; }
};

} //~namespace Music

} //~namespace ribi

#endif // MUSICSCALE_H
