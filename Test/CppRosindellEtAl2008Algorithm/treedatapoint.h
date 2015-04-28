#ifndef TREEDATAPOINT_H
#define TREEDATAPOINT_H

// this is a data object used in the routine for
// calculating the coalescence tree
// but does not form part of the output itself
// it is meant as a tool for performing the coalescence itself
// this object includes all the mechanism required for the indexing system
// indexing is what allows infinite areas to be simulated efficiently
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
  int GetXindex() const noexcept { return m_xindex; }
  int GetYindex() const noexcept { return m_yindex; }
  int GetMpos() const noexcept { return m_mpos; }
  int GetNext() const noexcept { return m_next; }
  int GetLast() const noexcept { return m_last; }
  double GetProbability() const noexcept { return m_probability; }

  void SetPos(const int xpos, const int ypos) noexcept { m_xpos = xpos; m_ypos = ypos; }
  void SetIndex(const int x, const int y) noexcept { m_xindex = x; m_yindex = y; }
  void SetMpos(const int mpos) noexcept { m_mpos = mpos; }
  void SetNext(const int next) noexcept { m_next = next; }
  void SetLast(const int last) noexcept { m_last = last; }
  void SetProbability(const double probability) { m_probability = probability; }
  // checks for coalescence with another datapoint
  // update the position of this datapoint
  // this implements the indexing system
  void Move(const int x, const int y, const double z);
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


#endif // TREEDATAPOINT_H
