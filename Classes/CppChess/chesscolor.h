#ifndef CHESSCOLOR_H
#define CHESSCOLOR_H

#include <iosfwd>
#include <string>
#include <vector>

#include "chessfwd.h"

namespace ribi {
namespace Chess {

enum class Color
{
  black, white, indeterminate, red, green, blue
};

struct ColorVersion
{
  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();
};

std::string ColorToStr(const Color c);
Player ColorToPlayer(const Color c);
std::ostream& operator<<(std::ostream& os, const Color c);

bool operator==(const Color color, const Player player);
bool operator==(const Player player, const Color color);
bool operator!=(const Color color, const Player player);
bool operator!=(const Player player, const Color color);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSCOLOR_H
