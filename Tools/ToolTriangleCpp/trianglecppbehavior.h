#ifndef TRIANGLECPPBEHAVIOR_H
#define TRIANGLECPPBEHAVIOR_H

#include <string>
#include <vector>

namespace ribi {
namespace tricpp {

/// Data structure for command line switches and file names.  This structure
///   is used (instead of global variables) to allow reentrancy.
///
/// Switches for the triangulator.
///   poly: -p switch.  refine: -r switch.
///   quality: -q switch.
///     minangle: minimum angle bound, specified after -q switch.
///     goodangle: cosine squared of minangle.
///     offconstant: constant used to place off-center Steiner points.
///   vararea: -a switch without number.
///   fixedarea: -a switch with number.
///     maxarea: maximum area bound, specified after -a switch.
///   usertest: -u switch.
///   regionattrib: -A switch.  convex: -c switch.
///   weighted: 1 for -w switch, 2 for -W switch.  jettison: -j switch
///   firstnumber: inverse of -z switch.  All items are numbered starting
///     from `firstnumber'.
///   edgesout: -e switch.  voronoi: -v switch.
///   neighbors: -n switch.  geomview: -g switch.
///   nobound: -B switch.  nopolywritten: -P switch.
///   nonodewritten: -N switch.  noelewritten: -E switch.
///   noiterationnum: -I switch.  noholes: -O switch.
///   noexact: -X switch.
///   order: element order, specified after -o switch.
///   nobisect: count of how often -Y switch is selected.
///   steiner: maximum number of Steiner points, specified after -S switch.
///   incremental: -i switch.  sweepline: -F switch.
///   dwyer: inverse of -l switch.
///   splitseg: -s switch.
///   conformdel: -D switch.  docheck: -C switch.
///   quiet: -Q switch.  verbose: count of how often -V switch is selected.
///   usesegments: -p, -r, -q, or -c switch; determines whether segments are
///     used at all.
///
/// Read the instructions to find out the meaning of these switches.
struct Behavior {
  /// Maximum number of characters in a file name (including the null).
  //static const int max_filename_size = 2048;

  /// Read the command line, identify switches, and set
  /// up options and file names.
  Behavior(const std::vector<std::string>& args);

  std::string m_areafilename;
  int m_conformdel;
  int m_convex;
  bool m_do_check;
  bool m_do_refine;
  int m_dwyer;
  std::string m_edgefilename;
  int m_edgesout;
  static const int m_firstnumber = 1;
  int m_fixedarea;
  int m_geomview;
  double m_goodangle;
  int m_incremental;
  std::string m_inelefilename;
  std::string m_innodefilename;
  std::string m_inpolyfilename;
  int m_jettison;
  double m_maxarea;
  double m_minangle;
  std::string m_neighborfilename;
  int m_neighbors;
  int m_nobisect;
  int m_nobound;
  int m_noelewritten;
  int m_noexact;
  int m_noholes;
  int m_noiterationnum;
  int m_nonodewritten;
  int m_nopolywritten;
  double m_offconstant;
  std::string m_offfilename;
  int m_order;
  std::string m_outelefilename;
  std::string m_outnodefilename;
  std::string m_outpolyfilename;
  static const bool m_poly = true;
  int m_quality;
  int m_quiet;
  int m_regionattrib;
  int m_splitseg;
  int m_steiner;
  int m_sweepline;
  int m_usertest;
  static const bool m_usesegments = true;
  int m_vararea;
  std::string m_vedgefilename;
  int m_verbosity; ///0: no verbosity, 1: verbose, +1: more verbose
  std::string m_vnodefilename;
  int m_voronoi;
  static const int m_weighted = 0;
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPBEHAVIOR_H
