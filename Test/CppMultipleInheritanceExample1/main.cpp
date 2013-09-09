#include <cassert>
#include <iostream>
#include <memory>
#include <string>

//Abstract base class
struct State
{
  virtual ~State() {}
  virtual const std::string ToStr() const = 0;
};

struct StateLoggedIn : public State
{
  const std::string ToStr() const { return "logged_in"; }
};

struct StateNotLoggedIn : public State
{
  const std::string ToStr() const { return "not_logged_in"; }
};

//Abstract base class
struct Administrator : public State
{
  virtual ~Administrator() {}
};

struct AdministratorLoggedIn : public Administrator, StateLoggedIn
{
  const std::string ToStr() const { return this->StateLoggedIn::ToStr(); }
};

struct AdministratorNotLoggedIn : public Administrator, StateNotLoggedIn
{
  const std::string ToStr() const { return this->StateNotLoggedIn::ToStr(); }
};


//Abstract base class
struct Participant : public State
{
  virtual ~Participant() {}
};

struct ParticipantLoggedIn : public Participant, StateLoggedIn
{
  const std::string ToStr() const { return this->StateLoggedIn::ToStr(); }
};

struct ParticipantNotLoggedIn : public Participant, StateNotLoggedIn
{
  const std::string ToStr() const { return this->StateNotLoggedIn::ToStr(); }
};

int main()
{

  std::shared_ptr<Administrator> a1(new AdministratorLoggedIn);
  std::shared_ptr<Administrator> a2(new AdministratorNotLoggedIn);
  std::shared_ptr<Participant> p1(new ParticipantLoggedIn);
  std::shared_ptr<Participant> p2(new ParticipantNotLoggedIn);

  assert(a1->ToStr() == p1->ToStr());
  assert(a2->ToStr() == p2->ToStr());
  std::cout << a1->ToStr() << '\n';
  std::cout << a2->ToStr() << '\n';
}

/* Screen output:

logged_in
not_logged_in
Press <RETURN> to close this window...

*/
