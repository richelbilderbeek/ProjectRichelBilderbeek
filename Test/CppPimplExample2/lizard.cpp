#include "lizard.h"

struct Lizard::LizardImpl
{
  LizardImpl(const Gender gender) noexcept;
  Gender GetGender() const noexcept;

  private:
  const Gender m_gender;
};

Lizard::Lizard(const Gender gender) noexcept
  : m_impl(std::make_shared<LizardImpl>(gender) )
{

}

Lizard::LizardImpl::LizardImpl(const Gender gender) noexcept
  : m_gender(gender)
{

}

Gender Lizard::LizardImpl::GetGender() const noexcept
{
  return m_gender;
}

Gender Lizard::GetGender() const noexcept
{
  return m_impl->GetGender(); //Forward to implementation
}
