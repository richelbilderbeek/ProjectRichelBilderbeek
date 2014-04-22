
#include <cassert>

#include <exception>

#include "chesscastling.h"
#include "trace.h"

bool ribi::Chess::CanStrToCastling(const std::string& s)
{
  return boost::xpressive::regex_match(s,GetCastlingRegex());
}

std::string ribi::Chess::CastlingToStr(const Castling castling)
{
  switch (castling)
  {
    case Castling::kingside: return "O-O";
    case Castling::queenside: return "O-O-O";
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown Castling");
}

const boost::xpressive::sregex ribi::Chess::GetCastlingRegex()
{
  static const boost::xpressive::sregex r {
    boost::xpressive::sregex::compile("(0|O)-(0|O)(-(0|O))?(\\+|\\#)?")
  };
  return r;
}

ribi::Chess::Castling ribi::Chess::StrToCastling(const std::string& s)
{
  assert(CanStrToCastling(s));
  if (s.substr(0,3) == "O-O"   || s.substr(0,3) == "0-0"  ) return Castling::kingside;
  if (s.substr(0,5) == "O-O-O" || s.substr(0,5) == "0-0-0") return Castling::queenside;
  #ifndef NDEBUG
  TRACE(s);
  #endif
  assert(!"Cannot convert std::string to Castling");
  throw std::logic_error("Cannot convert std::string to Castling");
}
