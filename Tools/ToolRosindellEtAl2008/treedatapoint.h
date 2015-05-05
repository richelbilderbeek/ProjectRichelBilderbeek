#ifndef TREEDATAPOINT_H
#define TREEDATAPOINT_H

#include <iosfwd>

struct TreeNode;

/// Tracks a lineage in probability and space
/// Probability: how likely is this lineage to exist?
/// Space: the lineage goes through individuals in a two-dimensional space

/// A Lineage allows for a high number of positions,
/// by supply a position within a tile
/// and a tile index

/// For example, the spot marked X may have:
/// PosX == 2, PosY == 1
/// TileX == 42, TileY == 23
///
///  |     |
/// -+-----+-
///  |     |
///  |  X  |
///  |     |
///  |     |
/// -+-----+-
///  |     |
struct TreeDataPoint
{


  TreeDataPoint(
    const int x = 0,
    const int y = 0,
    TreeNode * node = nullptr
  );
  TreeDataPoint(const TreeDataPoint&);
  TreeDataPoint& operator=(const TreeDataPoint&);

  int GetAbsoluteXpos() const noexcept;
  int GetAbsoluteYpos() const noexcept;
  int GetXpos() const noexcept { return m_xpos; }
  int GetYpos() const noexcept { return m_ypos; }
  int GetTileX() const noexcept { return m_xindex; }
  int GetTileY() const noexcept { return m_yindex; }
  TreeNode *  GetNode() const noexcept { return m_node; }
  double GetProbability() const noexcept { return m_probability; }

  void SetIndex(const int x, const int y) noexcept { m_xindex = x; m_yindex = y; }
  void SetNode(TreeNode * const node) noexcept { m_node = node; }
  void SetPos(const int xpos, const int ypos) noexcept { m_xpos = xpos; m_ypos = ypos; }
  void SetProbability(const double probability) { m_probability = probability; }

  //Move the data point and update its probability
  void Move(const int dx, const int dy, const double p);
private:

  int m_xpos;
  int m_ypos;

  ///Number of horizontal wraps around the torus
  int m_xindex;

  ///Number of vertical wraps around the torus
  int m_yindex;

  ///Output of this lineage
  TreeNode * m_node;

  /// the probability of not having speciated yet
  /// this is to allow the coalescence tree calculation to be stopped
  /// prematurely - saving many calculations with minimal loss in accuracy
  double m_probability;

  static const int sm_gridsize = 4000;
};

bool operator==(const TreeDataPoint& lhs, const TreeDataPoint& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const TreeDataPoint& point) noexcept;

#endif // TREEDATAPOINT_H
