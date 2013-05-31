#ifndef ABCFILE_H
#define ABCFILE_H

#include <iosfwd>
#include <string>
#include <tuple>
#include "musicfwd.h"

struct AbcFile
{
  AbcFile();

  ///Get the composer
  const std::string& GetComposer() const { return m_composer; }

  ///Get the composer
  int GetIndex() const { return m_index; }

  ///Get the title
  const std::string& GetTitle() const { return m_title; }

  ///Set the composer
  ///The 'C' field
  void SetComposer(const std::string& composer);

  ///Set the song index
  ///The 'X' field
  void SetIndex(const int index);

  ///Set the key, e.g. 'C'
  ///The 'K' field
  void SetKey(const Music::Note& note);

  ///Set the note length from a numerator and denominator, e.g. (1,4) becomes 1/4
  ///The 'L'
  void SetNoteLength(const int n, const int d);

  ///Set the tempo from a numerator and denominator and a beats per minute,
  ///e.g. (1,4,120) becomes 1/4=120
  ///The 'Q'
  void SetTempo(const int n, const int d, const int tempo);

  ///Set the time signature from a numerator and denominator, e.g. (3,4) becomes 3/4
  ///The 'M'
  void SetTimeSignature(const int n, const int d);

  ///Set the title
  ///The 'T' field
  void SetTitle(const std::string& title);

  ///Convert the ABC file to a text with lines
  const std::string ToStr() const;

  private:
  ///The 'C' field
  const std::string m_composer;

  ///The 'X' field
  const int m_index;

  ///The 'K' field
  const int m_note; //Use int used by Note its internals

  ///The 'L' field
  const std::pair<int,int> m_note_length;

  ///The 'T' field
  const std::tuple<int,int,int> m_tempo;

  ///The 'M' field
  const std::pair<int,int> m_time_signature;

  ///The 'T' field
  const std::string m_title;
};

std::ostream& operator<<(std::ostream& os, const AbcFile& file);

#endif // ABCFILE_H
