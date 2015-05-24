#ifndef PAPERROCKSCISSORSWITHTRAITINITIALIZATION_H
#define PAPERROCKSCISSORSWITHTRAITINITIALIZATION_H

#include <iosfwd>

namespace ribi {
namespace prswt { //Paper-Rock-Scissors-With-Trait

enum class Initialization
{
  random,
  vertical_bands,
  monomorph
};

std::string ToStr(const Initialization initialization) noexcept;
Initialization ToInitialization(const std::string& s);

std::ostream& operator<<(std::ostream& os, const Initialization initialization);
std::istream& operator>>(std::istream& is, Initialization& initialization);

#ifndef NDEBUG
void TestInitialization() noexcept;
#endif

} //~namespace prswt { //Paper-Rock-Scissors-With-Trait
} //~namespace ribi

#endif // PAPERROCKSCISSORSWITHTRAITINITIALIZATION_H
