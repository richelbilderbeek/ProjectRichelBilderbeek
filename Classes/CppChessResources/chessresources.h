#ifndef RIBI_CHESSRESOURCES_H
#define RIBI_CHESSRESOURCES_H

#include <boost/shared_ptr.hpp>
#include "chessfwd.h"
#include "chesscolor.h"

namespace ribi {
namespace Chess {

///Resources contains the resources filenames
struct Resources
{
  Resources() noexcept {}

  virtual ~Resources() noexcept {}

  ///Find the filename for this piece
  static std::string Find(
    const boost::shared_ptr<const Chess::Piece>& piece,
    const Chess::Color selection_color = Color::indeterminate,
    const bool big = false);

  ///Find the filename for this square
  static std::string Find(
    const boost::shared_ptr<const Square> square,
    const Chess::Color selection_color = Color::indeterminate);

  ///Find the filename for this selected piece
  //const std::string FindSelected(const boost::shared_ptr<const Chess::Piece>& piece) const;

  ///Get the Resources its only instance
  //static Resources * Get();

  ///Obtain all the resources' filenames
  static std::vector<std::string> GetFilenames() noexcept;

  //private:
  ///Resources its constructor, private because Resources is a Singleton
  //Resources();

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Resources its only instance
  //static Resources * m_instance;

  ///Tests this class for all files being present
  static void Test() noexcept;
};

} //~ namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSRESOURCES_H
