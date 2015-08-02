//Example that shows:
// - console at lower screen
// - graphics at top screen
// - use of STL

#include <nds.h>
#include <iostream>

int main()
{
  consoleDemoInit();
  videoSetMode(MODE_FB0);
  vramSetBankA(VRAM_A_LCD);

  std::cout
    << "\n"
    << " CppLibndsExample1\n"
    << " From\n"
    << " http://www.richelbilderbeek.nl\n"
    << "   /CppLibndsExample1.htm\n"
    << "\n"
    << " Press A and B keys for effect\n";

  //The maximum x coordinat
  const int maxx = 256;
  //The maximum y coordinat
  const int maxy = 192;
  //The maximum R/G/B color value
  const int max_color = 32;
  //Counter for the scroll effect
  int z = 0;

  while(1)
  {
    //Respond to keys
    scanKeys();
    const int held = keysHeld();
    if (!held) continue;
    if (held & KEY_A) ++z;
    if (held & KEY_B) { --z; if (z<0) z+=max_color; }
    for (int y=0; y!=maxy; ++y)
    {
      for (int x=0; x!=maxx; ++x)
      {
        VRAM_A[(y*maxx)+x]
          = RGB15(
            (x+z  ) % max_color,
            (y+z  ) % max_color,
            (x+y+z) % max_color);
      }
    }
  }
}
