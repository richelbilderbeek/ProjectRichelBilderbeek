#include "aafmoleculefactory.h"

#include <cassert>
#include <stdexcept>

#include "aafbond.h"

boost::shared_ptr<ribi::aaf::Molecule> ribi::aaf::MoleculeFactory::Create(
  const AminoAcid a
) const noexcept
{
  switch (a)
  {
    case AminoAcid::glycine: return CreateGlycine();
    default:
      assert(!"Should not get here");
      throw std::logic_error("ribi::aaf::MoleculeFactory::Create: unknown amino acid");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::aaf::MoleculeFactory::Create: unknown amino acid");
}

boost::shared_ptr<ribi::aaf::Molecule> ribi::aaf::MoleculeFactory::CreateGlycine() const noexcept
{
  typedef Molecule::Graph Graph;
  Graph g;

  //All vertex names
  //Note: cannot use spaces
  using namespace boost::units::si;
  const auto bond_length(GetAverageBondLength());
  typedef PolarCoordinat<Atom::Angle,Atom::Length> Coordinat;

  const double pi { boost::math::constants::pi<double>() };
  const int n_atoms { 10 };
  #ifndef NDEBUG
  const int n_bonds {  9 };
  #endif
  /*

  H   H   O
   \  |  //
    N-C-C
   /  |  \
  H   H   O-H

  8   1   5
   \  |  //
    4-0-2
   /  |  \
  7   3   6-9

  */
  std::vector<Coordinat> coordinats;
  coordinats.push_back(Coordinat(0.0 * radian,0.0 * bond_length));
  coordinats.push_back(Coordinat(0.0 * pi * radian,1.0 * bond_length));
  coordinats.push_back(Coordinat(0.5 * pi * radian,1.0 * bond_length));
  coordinats.push_back(Coordinat(1.0 * pi * radian,1.0 * bond_length));
  coordinats.push_back(Coordinat(1.5 * pi * radian,1.0 * bond_length));
  #ifndef TODO_RJCB
  coordinats.push_back(coordinats[2] + Coordinat(( 1.0 / 6.0) * pi * radian,1.0 * bond_length));
  coordinats.push_back(coordinats[2] + Coordinat(( 5.0 / 6.0) * pi * radian,1.0 * bond_length));
  coordinats.push_back(coordinats[4] + Coordinat(( 7.0 / 6.0) * pi * radian,1.0 * bond_length));
  coordinats.push_back(coordinats[4] + Coordinat((11.0 / 6.0) * pi * radian,1.0 * bond_length));
  coordinats.push_back(coordinats[6] + Coordinat(0.5 * pi * radian,1.0 * bond_length));
  #endif
  assert(n_atoms == static_cast<int>(coordinats.size()));

  std::vector<Atom> atoms;
  atoms.push_back(Atom(AtomType::C,coordinats[0]));
  atoms.push_back(Atom(AtomType::H,coordinats[1]));
  atoms.push_back(Atom(AtomType::C,coordinats[2]));
  atoms.push_back(Atom(AtomType::H,coordinats[3]));
  atoms.push_back(Atom(AtomType::N,coordinats[4]));
  atoms.push_back(Atom(AtomType::H,coordinats[5]));
  atoms.push_back(Atom(AtomType::O,coordinats[6]));
  atoms.push_back(Atom(AtomType::H,coordinats[7]));
  atoms.push_back(Atom(AtomType::H,coordinats[8]));
  atoms.push_back(Atom(AtomType::H,coordinats[9]));
  assert(n_atoms == static_cast<int>(atoms.size()));

  std::vector<Graph::vertex_descriptor> vertices;
  for (int i=0; i!=n_atoms; ++i)
  {
    vertices.push_back(boost::add_vertex(atoms[i],g));
  }

  /*

  H   H   O
   \  |  //
    N-C-C
   /  |  \
  H   H   O-H

  8   1   5
   \  |  //
    4-0-2
   /  |  \
  7   3   6-9

  i     b     f
   7    0    4
    e-3-a-1-c
   6    2    5
  h     d     g8j

  */

  std::vector<Bond> bonds;
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  bonds.push_back(Bond(2));
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  bonds.push_back(Bond());
  assert(n_bonds == static_cast<int>(bonds.size()));

  boost::add_edge(vertices[0],vertices[1],bonds[0],g);
  boost::add_edge(vertices[0],vertices[2],bonds[0],g);
  boost::add_edge(vertices[0],vertices[3],bonds[0],g);
  boost::add_edge(vertices[0],vertices[4],bonds[0],g);
  boost::add_edge(vertices[2],vertices[5],bonds[0],g);
  boost::add_edge(vertices[2],vertices[6],bonds[0],g);
  boost::add_edge(vertices[4],vertices[7],bonds[0],g);
  boost::add_edge(vertices[4],vertices[8],bonds[0],g);
  boost::add_edge(vertices[6],vertices[9],bonds[0],g);
  const boost::shared_ptr<Molecule> m {
    new Molecule(g)
  };
  assert(m);
  return m;
}
