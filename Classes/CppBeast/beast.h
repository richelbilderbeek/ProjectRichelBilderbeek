#ifndef RIBI_BEAST_H
#define RIBI_BEAST_H

#include <string>
#include <vector>

///Wrapper to call BEAST
struct Beast
{
  enum class GraphicsFormat { svg };

  Beast();

  void Run(const std::string& output_filename) const noexcept;

  private:
  static const std::string sm_beast_path;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif //RIBI_BEAST_H
