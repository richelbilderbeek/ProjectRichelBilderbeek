#ifndef QTCHESSRESOURCES_H
#define QTCHESSRESOURCES_H

#include <boost/shared_ptr.hpp>
#include "chessfwd.h"
#include "chessresources.h"

namespace Qt { struct QPixmap; }

namespace ribi {
namespace Chess {

///QtResources uses Qt for generating the chess resources
struct QtResources : public Chess::Resources
{
  //QtResources constructor does all the work
  QtResources();

  ///Obtain the QPixmap of a Piece
  const Qt::QPixmap& GetPiece(const Square& s) const;

  ///Obtain the QPixmap of a Square
  const Qt::QPixmap& GetSquare(const Square& s) const;

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();

  private:
  boost::shared_ptr<Qt::QPixmap> m_square_black;
  boost::shared_ptr<Qt::QPixmap> m_square_white;
};

} //~namespace Chess
} //~namespace ribi

#endif // QTCHESSRESOURCES_H
