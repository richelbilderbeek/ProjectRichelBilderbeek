#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct Gossip
{
  ~Gossip() { std::cout << "Gossip destructor\n"; }
};

int main()
{
  ///boost::shared_ptr automatically deletes its element when it
  ///goes out of scope
  {
    const boost::shared_ptr<const Gossip> p { new Gossip };
  }
  ///Read the element type of a boost::shared_ptr
  {
    typedef boost::shared_ptr<const Gossip> Type;
    const Type p { new Gossip };

    static_assert(std::is_same<Type::element_type,const Gossip>(),
      "Use element_type to read the type the boost::shared_ptr contains");
  }
  ///Use use_count
  {
    boost::shared_ptr<const Gossip> p;
    assert(p.use_count() == 0);
    p.reset( new Gossip );
    assert(p.use_count() == 1);
    {
      const boost::shared_ptr<const Gossip> q(p);
      assert(p.use_count() == 2);
    }
    assert(p.use_count() == 1);
  }
  ///Custom deleter for Gossip
  {
    const boost::shared_ptr<Gossip> p {
      new Gossip,
      [](const Gossip * const gossip)
      {
        std::cout << "Deleting Gossip with custom deleter\n";
        delete gossip;
        std::cout << "Deleted Gossip with custom deleter\n";
      }
    };
  }
}

/* Screen output:

Gossip destructor
Gossip destructor
Gossip destructor
Deleting Gossip with custom deleter
Gossip destructor
Deleted Gossip with custom deleter
Press <RETURN> to close this window...

*/
