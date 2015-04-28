#ifndef DISPERSALKERNEL_H
#define DISPERSALKERNEL_H

#include <iosfwd>

// 4.) dispersal kernel type (square if 0, normal if 1)
enum class DispersalKernel { square, normal };

std::string ToStr(const DispersalKernel kernel) noexcept;

std::ostream& operator<<(std::ostream& os, const DispersalKernel kernel) noexcept;
std::istream& operator>>(std::istream& is, DispersalKernel& kernel) noexcept;

#endif // DISPERSALKERNEL_H
