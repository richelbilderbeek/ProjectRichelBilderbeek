#ifndef TANKBATTALION_H
#define TANKBATTALION_H



struct TankBattalion
{
  struct Sprite
  {
    double x;
    double y;
    TankBattalion::SpriteType type;
  };


  TankBattalion();

  void PressKeyDown();
  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyUp();
  void Tick();

  static int GetArenaHeight() { return 176; }
  static int GetArenaWidth()  { return 168; }

  private:

};

#endif // TANKBATTALION_H
