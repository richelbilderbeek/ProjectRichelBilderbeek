#ifndef DASWAHRESCHLAGERFESTDISPLAY_H
#define DASWAHRESCHLAGERFESTDISPLAY_H

namespace ribi {

struct DasWahreSchlagerfestWidget;

struct DasWahreSchlagerfestDisplay
{
  virtual ~DasWahreSchlagerfestDisplay() {}
  virtual void Display(const DasWahreSchlagerfestWidget& widget) = 0;
  virtual void OnChanged(const DasWahreSchlagerfestWidget& widget) = 0;
};

} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTDISPLAY_H
