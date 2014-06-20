#include <cassert>
#include <memory>

enum class Gender { male, female };

struct Lizard
{
  Lizard(const Gender gender) noexcept;
  Gender GetGender() const noexcept;
  private:
  struct LizardImpl;
  const std::shared_ptr<const LizardImpl> m_impl;
};

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

Gender Lizard::GetGender() const noexcept
{
  return m_impl->GetGender(); //Forward to implementation
}

Lizard::LizardImpl::LizardImpl(const Gender gender) noexcept
  : m_gender(gender)
{

}

Gender Lizard::LizardImpl::GetGender() const noexcept
{
  return m_gender;
}


int main()
{
  const Lizard male(Gender::male);
  assert(male.GetGender() == Gender::male);
  const Lizard female(Gender::female);
  assert(female.GetGender() == Gender::female);
}
