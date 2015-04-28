#ifndef DISPERSALKERNEL_H
#define DISPERSALKERNEL_H

#include <iosfwd>

enum class DispersalKernel { square, normal };

std::string ToStr(const DispersalKernel kernel) noexcept;

std::ostream& operator<<(std::ostream& os, const DispersalKernel kernel) noexcept;

#endif // DISPERSALKERNEL_H
