#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>

#include "chesscastling.h"
#include "chessmove.h"
#include "chessmoves.h"
#include "chesspiece.h"
#include "chesspiecefactory.h"
#include "chessmovefactory.h"
#include "chesssquarefactory.h"
#include "chessscore.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::Move::Move(const std::string& s)
  : m_from(ParseFrom(s)),
    m_is_capture(ParseIsCapture(s)),
    m_is_castling(ParseIsCastling(s)),
    m_is_check(ParseIsCheck(s)),
    m_is_checkmate(ParseIsCheckmate(s)),
    m_is_en_passant(ParseIsEnPassant(s)),
    m_is_promotion(ParseIsPromotion(s)),
    m_piece(ParsePiece(s)),
    m_piece_promotion(ParsePiecePromotion(s)),
    m_score(ParseScore(s)),
    m_str(s),
    m_to(ParseTo(s))
{
  #ifndef NDEBUG
  Test();
  #endif

  if (s.empty()) throw std::logic_error("std::string to parse is empty");
  if (!m_to && !m_is_castling && (!m_score))
  {
    const std::string error = "Chess::ribi::Chess::Move::Move exception: m_to not initialized for non-castling non-score move " + s;
    throw std::logic_error(error.c_str());
  }
  if (!m_piece && !m_is_castling && !m_score)
  {
    const std::string error = "Chess::ribi::Chess::Move::Move exception: m_piece not initialized for non-castling non-score move " + s;
    throw std::logic_error(error.c_str());
  }

  if (m_is_en_passant && !m_is_capture) throw std::logic_error("Chess::ribi::Chess::Move::Move exception: every en passant capture is a capture");

  if (boost::xpressive::regex_search(s,boost::xpressive::sregex::compile("(e\\.p\\.)")) && !m_is_en_passant)
  {
    const std::string error = "Chess::ribi::Chess::Move::Move exception: move is an invalid en passant move: " + s;
    throw std::logic_error(error.c_str());
  }

  if (m_piece)
  {
    if (m_is_castling)
    {
      throw std::logic_error("Chess::ribi::Chess::Move::Move exception: m_piece cannot be initialized in a castling move");
    }
    if (m_score) throw std::logic_error("Chess::ribi::Chess::Move::Move exception: m_piece cannot be initialized in a score move");
    const bool valid = m_piece->CanDoMove(this);
    if (!valid)
    {
      const std::string t = "Move " + s + " invalid for " + m_piece->GetName();
      throw std::logic_error(t.c_str());
    }
  }
}

std::vector<std::string> ribi::Chess::Move::GetRegexMatches(
  const std::string& s,
  const boost::xpressive::sregex& r)
{
  std::vector<std::string> v;
  boost::xpressive::sregex_iterator cur(s.begin(),s.end(),r);
  boost::xpressive::sregex_iterator end;
  for( ; cur != end; ++cur )
  {
    const boost::xpressive::smatch& what = *cur;
    v.push_back(what[0]);
  }
  return v;
}

std::string ribi::Chess::Move::GetVersion()
{
  return "1.1";
}

std::vector<std::string> ribi::Chess::Move::GetVersionHistory()
{
  return {
    "2012-01-25: version 1.0: initial version"
    "2013-11-08: version 1.1: replaced Boost.Regex by Boost.Xpressive"
  };
}

bool ribi::Chess::Move::IsCastling() const
{
  assert(!m_is_castling || CanStrToCastling(m_str));
  return m_is_castling;
}

boost::shared_ptr<ribi::Chess::Square> ribi::Chess::Move::ParseFrom(const std::string& s)
{
  boost::shared_ptr<Chess::Square> square;
  static const boost::xpressive::sregex r { boost::xpressive::sregex::compile("[a-h][1-8]") };
  const std::vector<std::string> v = GetRegexMatches(s,r);
  #ifndef NDEBUG
  if (!(v.size() <= 2)) { TRACE(s); }
  #endif
  assert(v.size() <= 2);
  if (v.size() == 2)
  {
    square = SquareFactory::Create(v[0]);
  }
  return square;
}

bool ribi::Chess::Move::ParseIsCapture(const std::string& s)
{
  //if (s.empty()) throw std::logic_error("ribi::Chess::Move::ParseIsCapture exception: move must not be empty");
  //return boost::regex_match(s,boost::regex("[a-h]\\d?x.*"));
  static const boost::xpressive::sregex r {
    boost::xpressive::sregex::compile("(B|K|N|Q|R)?([a-h])?([1-8])?x[a-h][1-8](e.p.)?(\\+|\\#)?")
  };
  return boost::xpressive::regex_match(s,r);
}

bool ribi::Chess::Move::ParseIsCastling(const std::string& s)
{
  return CanStrToCastling(s);

  //return s == "0-0" || s == "O-O" || s == "O-O+" || s == "0-0-0" || s == "O-O-O"|| s == "O-O-O+";
}

bool ribi::Chess::Move::ParseIsCheck(const std::string& s)
{
  if (s.empty()) throw std::logic_error("ribi::Chess::Move::IsCheck(const std::string& s) exception: move must not be empty");
  return s[s.size() - 1] == '+';
}

bool ribi::Chess::Move::ParseIsCheckmate(const std::string& s)
{
  if (s.empty()) throw std::logic_error("ribi::Chess::Move::IsCheckmate(const std::string& s) exception: move must not be empty");
  return s[s.size() - 1] == '#';
}

bool ribi::Chess::Move::ParseIsEnPassant(const std::string& s)
{
  static const boost::xpressive::sregex r {
    boost::xpressive::sregex::compile("([a-h][4-5])x[a-h][3-6]e.p.(\\+|\\#)?")
  };

  if (!boost::xpressive::regex_match(s,r)) return false;
  const boost::shared_ptr<Chess::Square> from = ParseFrom(s);
  const boost::shared_ptr<Chess::Square> to = ParseTo(s);
  assert(from);
  assert(to);
  if (std::abs(from->GetFile().ToInt() - to->GetFile().ToInt()) != 1) return false;
  if (std::abs(from->GetRank().ToInt() - to->GetRank().ToInt()) != 1) return false;
  if (from->GetRank() == Chess::Rank("5") && to->GetRank() == Chess::Rank("6")) return true;
  if (from->GetRank() == Chess::Rank("4") && to->GetRank() == Chess::Rank("3")) return true;
  return false;
}

bool ribi::Chess::Move::ParseIsPromotion(const std::string& s)
{
  static const boost::xpressive::sregex r {
    boost::xpressive::sregex::compile("([a-h][1-8](x|\\s)?)?[a-h][1|8][B|N|Q|R](\\+|\\#)?")
  };
  return boost::xpressive::regex_match(s,r);
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::Move::ParsePiece(const std::string& s)
{
  if (s.empty()) throw std::logic_error("ribi::Chess::Move::ParsePiece exception: move must not be empty");
  const char namechar = s[0];
  boost::shared_ptr<ribi::Chess::Square> square;
  switch (namechar)
  {
    case 'B':
    case 'K':
    case 'N':
    case 'Q':
    case 'R':
      assert(s.size() >= 3);
      square = SquareFactory().Create(s.substr(1,2));
      break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
      assert(s.size() >= 2);
      square = SquareFactory().Create(s.substr(0,2));
      break;
    default:
      throw std::logic_error("ribi::Chess::Move::ParsePiece exception: piece type cannot be determined");
  }

  const Color color = Color::indeterminate;


  boost::shared_ptr<Chess::Piece> p;
  switch (namechar)
  {
    case 'B': p = PieceFactory().CreateBishop(color,square); break;
    case 'K': p = PieceFactory().CreateKing(color,square); break;
    case 'N': p = PieceFactory().CreateKnight(color,square); break;
    case 'Q': p = PieceFactory().CreateQueen(color,square); break;
    case 'R': p = PieceFactory().CreateRook(color,square); break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
      p = PieceFactory().CreatePawn(color,square); break;
    default:
      throw std::logic_error("ribi::Chess::Move::ParsePiece exception: piece type cannot be determined");
  }
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::Move::ParsePiecePromotion(const std::string& s)
{
  if (s.empty()) throw std::logic_error("ribi::Chess::Move::ParsePiece exception: move must not be empty");
  const boost::shared_ptr<Chess::Piece> p = PieceFactory().CreateFromPromotion(s);
  assert((p || !p) && "Allow a nullptr if a string cannot be parsed to a promoted piece");
  return p;
}

boost::shared_ptr<ribi::Chess::Score> ribi::Chess::Move::ParseScore(const std::string& s)
{
  boost::shared_ptr<Chess::Score> p;
  try
  {
    Chess::Score * const ptr = new Chess::Score(s);
    p.reset(ptr);
  }
  catch (std::exception& e)
  {
    //Move is not a Score, no problem
  }
  return p;
}

boost::shared_ptr<ribi::Chess::Square> ribi::Chess::Move::ParseTo(const std::string& s)
{
  static const boost::xpressive::sregex r {
    boost::xpressive::sregex::compile("[a-h][1-8]")
  };

  boost::shared_ptr<Chess::Square> square;
  const std::vector<std::string> v = GetRegexMatches(s,r);
  if (!v.empty())
  {
    assert(v.size() <= 2);
    const std::string t = v[ v.size() - 1];
    square = SquareFactory::Create(t);
    assert(square);
  }
  return square;
}

std::string ribi::Chess::Move::ToStr() const
{
  std::string s;
  if (m_piece)
  {
    if (!dynamic_cast<PiecePawn*>(m_piece.get()))
    {
      s += m_piece->GetNameChar();
    }
    if (m_from)
    {
      s += m_from->ToStr();
    }
    else
    {
      s += "??";
    }
    if (m_is_capture)
    {
      s += "x";
    }
    else
    {
      s += " ";
    }
    if (m_to)
    {
      s += m_to->ToStr();
    }
    else
    {
      s += "??";
    }
  }
  if (m_is_castling) s += m_str;
  if (m_is_check) s+= "+";
  if (m_is_checkmate) s+= "#";
  if (m_is_en_passant) s+= "e.p.";
  if (m_is_promotion) s+= "(promotion)";
  if (m_piece_promotion) s+= m_piece_promotion->GetNameChar();
  if (m_score) s+= m_score->ToStr();
  return s;
}

bool ribi::Chess::operator==(const Move& lhs, const Move& rhs)
{
  if (static_cast<bool>(lhs.m_from) != static_cast<bool>(rhs.m_from)) return false;
  if (lhs.m_from)
  {
    assert(rhs.m_from);
    if (*lhs.m_from != *rhs.m_from) return false;
  }
  if (lhs.m_is_capture  != rhs.m_is_capture) return false;
  if (lhs.m_is_castling != rhs.m_is_castling) return false;
  if (lhs.m_is_check != rhs.m_is_check) return false;
  if (lhs.m_is_checkmate != rhs.m_is_checkmate) return false;
  if (lhs.m_is_en_passant != rhs.m_is_en_passant) return false;
  if (lhs.m_is_promotion != rhs.m_is_promotion) return false;
  if (static_cast<bool>(lhs.m_piece) != static_cast<bool>(rhs.m_piece)) return false;
  if (lhs.m_piece)
  {
    assert(rhs.m_piece);
    if (*lhs.m_piece != *rhs.m_piece) return false;
  }

  if (static_cast<bool>(lhs.m_piece_promotion) != static_cast<bool>(rhs.m_piece_promotion)) return false;
  if (lhs.m_piece_promotion)
  {
    assert(rhs.m_piece_promotion);
    if (*lhs.m_piece_promotion != *rhs.m_piece_promotion) return false;
  }

  if (static_cast<bool>(lhs.m_score) != static_cast<bool>(rhs.m_score)) return false;
  if (lhs.m_piece_promotion)
  {
    assert(rhs.m_score);
    if (*lhs.m_score!= *rhs.m_score) return false;
  }

  return true;
}

bool ribi::Chess::operator!=(const Move& lhs, const Move& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::Chess::operator<<(std::ostream& os,const Move& m)
{
  os << m.GetStr();
  return os;
}
