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
    const unsigned short x = 0,
    const unsigned short y = 0,
    const unsigned int z = 0
  );
  TreeDataPoint(const TreeDataPoint&);
  TreeDataPoint& operator=(const TreeDataPoint&);

  void SetPos(unsigned short any_xpos, unsigned short any_ypos) noexcept { m_xpos = any_xpos; m_ypos = any_ypos; }
  void SetIndex( short x , short y) noexcept { m_xindex = x; m_yindex = y; }
  void SetMpos(unsigned int z) { m_mpos = z; }
  void SetNext(unsigned int x) { m_next = x; }
  void SetLast(unsigned int x) { m_last = x; }
  void SetProbability(double x) { m_probability = x; }
  unsigned short GetXpos() const noexcept { return m_xpos; }
  unsigned short GetYpos() const noexcept { return m_ypos; }
  short GetXindex() const noexcept { return m_xindex; }
  short GetYindex() const noexcept { return m_yindex; }
  unsigned int GetMpos() const noexcept { return m_mpos; }
  unsigned int GetNext() const noexcept { return m_next; }
  unsigned int GetLast() const noexcept { return m_last; }
  double GetProbability() const noexcept { return m_probability; }
  // checks for coalescence with another datapoint
  // update the position of this datapoint
  // this implements the indexing system
  void Move(const short x,const short y,const double z);
private:
  unsigned short m_xpos;
  unsigned short m_ypos;
  /// number of wraps of x around the torus
  short m_xindex;
  /// number of wraps of y around the torus
  short m_yindex;
  /// the next individual in the loop of those that have the same xypos
  unsigned int m_next;
  /// the last individual in the loop 0 means the only one
  unsigned int m_last;
  /// points to the position in output of this lineage
  unsigned int m_mpos;
  /// the probability of not having speciated yet
  /// this is to allow the coalescence tree calculation to be stopped
  /// prematurely - saving many calculations with minimal loss in accuracy
  double m_probability;

  static const int sm_gridsize = 4000;
};
#endif // TREEDATAPOINT_H
