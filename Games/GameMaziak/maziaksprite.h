#ifndef MAZIAKSPRITE_H
#define MAZIAKSPRITE_H

namespace ribi {
namespace maziak {

enum class Sprite
{
  //Floor
  empty,
  wall,
  path,
  transparent,
  //Player sprites
  player_look_down,
  player_look_down_sword,
  player_look_left,
  player_look_left_sword,
  player_look_right,
  player_look_right_sword,
  player_look_up,
  player_look_up_sword,
  player_walk_left1,
  player_walk_left2,
  player_walk_left_sword1,
  player_walk_left_sword2,
  player_walk_right1,
  player_walk_right2,
  player_walk_right_sword1,
  player_walk_right_sword2,
  player_walk_down1,
  player_walk_down2,
  player_walk_down_sword1,
  player_walk_down_sword2,
  player_walk_up1,
  player_walk_up2,
  player_walk_up_sword1,
  player_walk_up_sword2,
  player_won1,
  player_won2,
  //Fighting sprites
  fight_sword1,
  fight_no_sword1,
  fight2,
  fight3,
  fight4,
  fight_won1,
  fight_won2,
  fight_lost1,
  fight_lost2,
  //Non-player sprites
  enemy1,
  enemy2,
  prisoner1,
  prisoner2,
  sword,
  exit,

  n_sprites //Never use, used for debugging
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITE_H
