#ifndef WTCHESSRESOURCES_H
#define WTCHESSRESOURCES_H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "chessfwd.h"
#include "chessresources.h"
//---------------------------------------------------------------------------
namespace Chess { struct Piece; }
namespace Wt { struct QPixmap; }
//---------------------------------------------------------------------------
namespace Chess {
//---------------------------------------------------------------------------
///WtResources uses Wt for generating the chess resources
struct WtResources : public Chess::Resources
{
  //WtResources constructor does all the work
  WtResources();

  ///Obtain the QPixmap of a Piece
  const Wt::QPixmap& GetPiece(const Square& s) const;

  ///Obtain the QPixmap of a Square
  const Wt::QPixmap& GetSquare(const Square& s) const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  boost::shared_ptr<Wt::QPixmap> m_square_black;
  boost::shared_ptr<Wt::QPixmap> m_square_white;
};
//---------------------------------------------------------------------------
} //~ namespace Chess
//---------------------------------------------------------------------------
#endif // WTCHESSRESOURCES_H
