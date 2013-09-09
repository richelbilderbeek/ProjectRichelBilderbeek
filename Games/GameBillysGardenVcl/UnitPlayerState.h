//---------------------------------------------------------------------------

#ifndef UnitPlayerStateH
#define UnitPlayerStateH
//---------------------------------------------------------------------------
struct Player;
//---------------------------------------------------------------------------
struct PlayerState
{
  PlayerState(Player& player);
  virtual ~PlayerState() {}
  virtual void PressKeyLeft()  = 0;
  virtual void PressKeyRight() = 0;
  virtual void PressKeyJump()  = 0;
  virtual void PressNoKey()    = 0;
  virtual void Tick(double& x, double& y) = 0;
  const Extctrls::TImage * const GetSprite() const { return m_sprite; }
  const int GetHeight() const;
  const int GetWidth() const;

  protected:
  Player& m_player;
  const Extctrls::TImage * m_sprite;
  const double m_walk_speed;
  const double m_jump_up_speed;
  const double m_gravity;
  const double m_ddx; //Change of dx on key press left and right 
};
//---------------------------------------------------------------------------
struct PlayerJump : public PlayerState
{
  PlayerJump(Player& player);
  void PressKeyLeft() { m_dx-=m_ddx; }
  void PressKeyRight() { m_dx+=m_ddx;}
  void PressKeyJump() {}
  void PressNoKey() {}
  void Tick(double& x, double& y)
  {
    x+=m_dx;
    y+=m_dy;
    m_dy+=m_gravity;
  }
  void StartJump(const double dx) //Is jump forward, backwards or up?
  {
    m_dy = -m_jump_up_speed;
    m_dx = dx;
    m_sprite = (m_dx >= 0.0 ? m_jump_right : m_jump_left);
  }
  void EndJump();

  double m_dy;
  double m_dx;

  private:
  const Extctrls::TImage * const m_jump_left;
  const Extctrls::TImage * const m_jump_right;
};
//---------------------------------------------------------------------------
struct PlayerLeft : public PlayerState
{
  PlayerLeft(Player& player);
  void PressKeyLeft() {}
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey();
  void StartLeft()
  {
    m_sprite = m_walk_left_1;
  }
  void Tick(double& x, double& y)
  {
    x-=m_walk_speed;
    m_sprite = (m_sprite == m_walk_left_2 ? m_walk_left_1 : m_walk_left_2);
  }

  private:
  const Extctrls::TImage * const m_walk_left_1;
  const Extctrls::TImage * const m_walk_left_2;

};
//---------------------------------------------------------------------------
struct PlayerRight : public PlayerState
{
  PlayerRight(Player& player);
  void PressKeyLeft();
  void PressKeyRight() {}
  void PressKeyJump();
  void PressNoKey();
  void StartRight()
  {
    m_sprite = m_walk_right_1;
  }
  void Tick(double& x, double& y)
  {
    x+=m_walk_speed;
    m_sprite = (m_sprite == m_walk_right_2 ? m_walk_right_1 : m_walk_right_2);
  }

  private:
  const Extctrls::TImage * const m_walk_right_1;
  const Extctrls::TImage * const m_walk_right_2;

};
//---------------------------------------------------------------------------
struct PlayerStand : public PlayerState
{
  PlayerStand(Player& player);
  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey() {}
  void StartStand(const bool face_right)
  {
    m_face_right = face_right;
    m_sprite = (m_face_right ? m_stand_right : m_stand_left);
  }
  void Tick(double& x, double& y) {}

  private:

  bool m_face_right; //Facing right direction
  const Extctrls::TImage * const m_stand_left;
  const Extctrls::TImage * const m_stand_right;
};
//---------------------------------------------------------------------------



#endif
