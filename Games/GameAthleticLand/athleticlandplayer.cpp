#include "athleticlandbackground.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QPixmap>
#include "athleticlandplayer.h"
#include "athleticlandplayerstate.h"
#pragma GCC diagnostic pop

ribi::athl::Player::Player()
  :
    m_state(PlayerState::stand_right),
    m_x(0.10),
    m_y(0.60)
    //m_state_left(boost::shared_ptr<PlayerLeft>(new PlayerLeft(*this))),
    //m_state_right(boost::shared_ptr<PlayerRight>(new PlayerRight(*this))),
    //m_state_jump(boost::shared_ptr<PlayerJump>(new PlayerJump(*this))),
    //m_state_stand(boost::shared_ptr<PlayerStand>(new PlayerStand(*this)))
{
  //SetStateStand(1.0); //1.0 = sprite looks to right
  //assert(m_cur_state);
}

void ribi::athl::Player::PressKeyLeft()
{
  switch (m_state)
  {
    case PlayerState::stand_left: m_x -= 0.01; break;
    case PlayerState::stand_right: m_state = PlayerState::stand_right; break;
    case PlayerState::n_types:
      assert(!"ribi::athl::Player::PressKeyLeft: never use PlayerState::n_types");
      throw std::logic_error("ribi::athl::Player::PressKeyLeft: never use PlayerState::n_types");
  }
}

void ribi::athl::Player::PressKeyRight()
{
    //case State::stand_right: m_x += 0.01; break;
    //case State::stand_left: m_state = State::stand_left;
}

void ribi::athl::Player::PressKeyJump()
{
  //m_cur_state->PressKeyJump();
}

void ribi::athl::Player::PressNoKey()
{
  //m_cur_state->PressNoKey();
}

/*
void ribi::athl::Player::Tick()
{
  m_cur_state->Tick(m_x,m_y);
}

void ribi::athl::Player::Draw(QPixmap * const canvas) const
{
  //assert(canvas);
  //assert(m_cur_state);
  //const int x = static_cast<int>(m_x);
  //const int y = static_cast<int>(m_y);
  //canvas->Draw(x,y,m_image->Picture->Graphic);
  //canvas->Draw(x,y,m_cur_state->GetSprite()->Picture->Graphic);
}

int ribi::athl::Player::GetHeight() const
{
  return m_cur_state->GetHeight();
}

int ribi::athl::Player::GetWidth() const
{
  return m_cur_state->GetWidth();
}

void ribi::athl::Player::Move(const int dx, const int dy)
{
  m_x +=static_cast<double>(dx);
  m_y +=static_cast<double>(dy);
}


void ribi::athl::Player::SetToWalkingHeight(const Background* const background)
{
  const int sprite_height = m_cur_state->GetHeight();
  const int y = background->m_walk_height - sprite_height;
  m_y = static_cast<double>(y);
}

void ribi::athl::Player::SetToStartingPosition(const Background* const background)
{
  SetToWalkingHeight(background);
  m_x = 0.0;
  this->SetStateStand(true);
}

void ribi::athl::Player::RespondToBackground(const Background* const background)
{
  //Prevent player from leaving the screen to the left
  if (m_x < 0.0) m_x = 0.0;

  //Prevent player from sinking down the screen after jumping
  const int sprite_height = m_cur_state->GetHeight();
  const int y = static_cast<int>(m_y);
  const int max_y = background->m_walk_height - sprite_height;
  if (y > max_y)
  {
    m_y = max_y;
    PlayerJump * const s = dynamic_cast<PlayerJump*>(this->m_cur_state);
    assert(s && "Player must have been jumping");
    s->EndJump();
  }
}

void ribi::athl::Player::SetStateLeft()
{
  //m_state_left->StartLeft();
  //An upcast, always successful
  //m_cur_state = dynamic_cast<PlayerState*>(m_state_left.get());
}

void ribi::athl::Player::SetStateRight()
{
  //m_state_right->StartRight();
  //An upcast, always successful
  //m_cur_state = dynamic_cast<PlayerState*>(m_state_right.get());
}

void ribi::athl::Player::SetStateJump(const double dx)
{
  //m_state_jump->StartJump(dx);
  //An upcast, always successful
  //m_cur_state = dynamic_cast<PlayerState*>(m_state_jump.get());
}

void ribi::athl::Player::SetStateStand(const bool face_right)
{
  //m_state_stand->StartStand(face_right);
  //An upcast, always successful
  //m_cur_state = dynamic_cast<PlayerState*>(m_state_stand.get());
}
*/
