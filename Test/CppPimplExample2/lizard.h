#ifndef LIZARD_H
#define LIZARD_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

enum class Gender { male, female };

struct Lizard
{
  Lizard(const Gender gender) noexcept;
  Gender GetGender() const noexcept;
  private:
  struct LizardImpl;
  const std::shared_ptr<const LizardImpl> m_impl;
};

#endif // LIZARD_H
