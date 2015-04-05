#ifndef PEDIGREE_H
#define PEDIGREE_H

#include <memory>
#include <vector>
struct Pedigree : public std::enable_shared_from_this<Pedigree>
{

  Pedigree(
    const std::string& name = "",
    const std::weak_ptr<Pedigree> parent = std::weak_ptr<Pedigree>()
  );
  ~Pedigree();

  ///Make an individual clean its deleted offspring
  void CheckOffspring() const;

  ///Start a Pedigree its ancestor
  static std::shared_ptr<Pedigree> Create(const std::string& name = "") noexcept;

  ///Create an offspring from this Pedigree member
  std::shared_ptr<Pedigree> CreateOffspring(const std::string& name = "") noexcept;

  ///Get the name of this Pedigree member
  const std::string& GetName() const noexcept { return m_name; }

  ///Get all current offspring of this Pedigree member
  ///May contain weak_ptrs that are nullptr, call CheckOffspring to let these be removed
  std::vector<std::weak_ptr<Pedigree>>& GetOffspring() const noexcept { return m_offspring; }

  ///Get the ancestor of this Pedigree member, might be nullptr
  std::weak_ptr<Pedigree> GetParent() const noexcept { return m_parent; }

  ///Set the name of this Pedigree member
  void SetName(const std::string& name) noexcept { m_name = name; }

  ///Create the pedigree of this member in Newick format
  std::string ToNewick() const;

  ///Set the ancestor of this Pedigree member
  void SetParent(const std::weak_ptr<Pedigree> parent) { m_parent = parent; }

  ///Set verbosity of this class
  void SetVerbose(const bool verbose) { m_verbose = verbose; }

  private:
  std::string m_name;
  mutable std::vector<std::weak_ptr<Pedigree>> m_offspring;
  std::weak_ptr<Pedigree> m_parent;
  bool m_verbose;

  ///Collect the std::string and depth of the offspring combined
  std::pair<std::string,int> CollectNameDepthPair() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

/*
newick <- "(A):0;" # OK, but not plottable
newick <- "(A:0);" # OK, but not plottable
newick <- "(A:1);" # OK, but not plottable
newick <- "(A:1,B:1);" # OK
newick <- "(A:1,B:1):0;" # OK
newick <- "(A:1,B:1):1;" # OK
newick <- "(A:1,B:1):1,C:1;" # FAILS
newick <- "(A:1,B:1):1,C;" # FAILS
newick <- "(A:1,B:1):1,C:1;" # FAILS
newick <- "(C:2,(A:1,B:1):1);" # OK
newick <- "((A:1,B:1):1,C:1);" # OK
*/

#endif // PEDIGREE_H
