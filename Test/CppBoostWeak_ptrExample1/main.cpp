#include <iostream>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <boost/weak_ptr.hpp>
#pragma GCC diagnostic pop

///A person with an ID
struct Person
{
  ///Create a Person with an ID
  Person(const int id) : m_id{id} {}

  ///Get the Person his/her ID
  int GetId() const { return m_id; }

  ///Change the Person his/her ID
  void SetId(const int id) { m_id = id; }

  private:
  ///Only allow a Boost smart pointer to delete Person,
  ~Person() {}
  ///Only allow a Boost smart pointer to delete Person,
  friend void boost::checked_delete<>(Person*);

  ///The Person his/her ID
  int m_id;
};

///A Person database with a single Person
struct Database
{
  ///Create a single Person (but more is possible as well)
  Database() : m_persons{}
  {
    //Create a single person
    m_persons.push_back(boost::shared_ptr<Person>(new Person(1)));
  }

  ///Remove all Persons from the Database
  void Clear()
  {
    m_persons.resize(0);
  }

  ///Get the first Person as a read-only pointer
  const Person * GetFirst1()
  {
    return m_persons[0].get(); //Created from a Person*
  }

  ///Get the first Person as a read-only boost::weak_ptr pointer
  const boost::weak_ptr<const Person> GetFirst2()
  {
    return m_persons[0]; //Created from a boost::shared_ptr<Person>
  }

  private:
  ///The Persons
  std::vector<boost::shared_ptr<Person> > m_persons;
};


int main()
{
  //Create a database
  Database d;

  //Obtain pointers to the first object
  const Person * const p1 = d.GetFirst1();
  const boost::weak_ptr<const Person> p2 = d.GetFirst2();
  assert(p1->GetId() == 1);
  assert(p2.use_count() == 1);

  //To read from a boost::weak_ptr, a boost::shared_ptr
  //must be created from it
  if (boost::shared_ptr<const Person> r = p2.lock())
  {
    assert(p1->GetId() == r->GetId());
    //delete p1; //Good: does not not compile
    //delete r.get(); //Good: does not not compile
    //p1->SetId(-1); //Good: does not not compile
    //r->SetId(-1); //Good: does not not compile
    assert(p2.use_count() == 2);
    assert(r.use_count() == 2);
  }

  //Kill the person in the database,
  //possibly resulting in dangling pointers!
  d.Clear();

  //assert(p1->GetId() == 1); //Bad: use of dangling pointer! Not detectable!
  assert(p2.use_count() == 0); //Good: dangling pointer is detected

  if (boost::shared_ptr<const Person> r = p2.lock())
  {
    assert(!"Bad: should not get here! ");
    assert(r->GetId() == -1 && !"Bad: use of dangling pointer!"); //Will not get here!
  }
  std::clog << "Good: dangling pointer is not used\n";
}
