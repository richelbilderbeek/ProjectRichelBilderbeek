#ifndef NSANABROSSPRITE_H
#define NSANABROSSPRITE_H
//---------------------------------------------------------------------------
#include <iosfwd>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
///An NsanaBrosSprite is a sprite, that is
///any visual element to be displayed on screen
///(either 1D or 2D)
struct NsanaBrosSprite : public boost::noncopyable
{
  NsanaBrosSprite(
    const double x = 0.0,
    const double y = 0.0,
    const double width = 0.0,
    const double height = 0.0,
    const int red = 0,
    const int green = 0,
    const int blue = 0);

  double GetBottom() const { return m_y + m_height; }
  double GetHeight() const { return m_height; }
  double GetLeft() const { return m_x; }
  double GetRight() const { return m_x + m_width; }
  double GetTop() const { return m_y; }
  double GetWidth() const { return m_width; }
  double GetX() const { return m_x; }
  double GetY() const { return m_y; }
  int GetRed() const { return m_red; }
  int GetGreen() const { return m_green; }
  int GetBlue() const { return m_blue; }
  //bool IsInRect(const double x, const double y) const;
  void Translate(const double dx, const double dy);

  const std::pair<double,double> GetCollisionVector(const NsanaBrosSprite* sprite) const;
  const std::pair<double,double> GetCollisionVectorFromPoint(const double x, const double y) const;

  private:
  ~NsanaBrosSprite() {}
  friend void boost::checked_delete<>(NsanaBrosSprite *);

  double m_x;
  double m_y;
  double m_width;
  double m_height;
  int m_red;
  int m_green;
  int m_blue;


  public:

  static void BothMoveAway(NsanaBrosSprite& r1, NsanaBrosSprite& r2);
  static void MoveAway(const NsanaBrosSprite& r1, NsanaBrosSprite& r2);
  static bool IsInRect(const double x, const double y, const NsanaBrosSprite& r);

};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const NsanaBrosSprite * const s);
//---------------------------------------------------------------------------
#endif // NSANABROSSPRITE_H
