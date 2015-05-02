#ifndef TREEDATAPOINT_H
#define TREEDATAPOINT_H

#include <iosfwd>

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
    const int mpos = 0
  );
  TreeDataPoint(const TreeDataPoint&);
  TreeDataPoint& operator=(const TreeDataPoint&);

  int GetXpos() const noexcept { return m_xpos; }
  int GetYpos() const noexcept { return m_ypos; }
  int GetTileX() const noexcept { return m_xindex; }
  int GetTileY() const noexcept { return m_yindex; }
  int GetLast() const noexcept { return m_last; }
  int GetMpos() const noexcept { return m_mpos; }
  int GetNext() const noexcept { return m_next; }
  double GetProbability() const noexcept { return m_probability; }

  void SetIndex(const int x, const int y) noexcept { m_xindex = x; m_yindex = y; }
  void SetNext(const int next) noexcept { m_next = next; }
  void SetLast(const int last) noexcept { m_last = last; }
  void SetMpos(const int mpos) noexcept { m_mpos = mpos; }
  void SetPos(const int xpos, const int ypos) noexcept { m_xpos = xpos; m_ypos = ypos; }
  void SetProbability(const double probability) { m_probability = probability; }
  // checks for coalescence with another datapoint
  // update the position of this datapoint
  // this implements the indexing system
  void Move(const int dx, const int dy, const double p);
private:
  int m_xpos;
  int m_ypos;

  ///Number of horizontal wraps around the torus
  int m_xindex;

  ///Number of vertical wraps around the torus
  int m_yindex;

  /// the next individual in the loop of those that have the same xypos
  int m_next;

  /// the last individual in the loop 0 means the only one
  int m_last;

  /// points to the position in output of this lineage
  int m_mpos;

  /// the probability of not having speciated yet
  /// this is to allow the coalescence tree calculation to be stopped
  /// prematurely - saving many calculations with minimal loss in accuracy
  double m_probability;

  static const int sm_gridsize = 4000;
};

bool operator==(const TreeDataPoint& lhs, const TreeDataPoint& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const TreeDataPoint& point) noexcept;

#endif // TREEDATAPOINT_H
