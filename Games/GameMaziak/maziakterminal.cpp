#include "maziakterminal.h"

#include "textcanvas.h"
#include "maziakmaindialog.h"
#include "maziaksprites.h"

ribi::maziak::Terminal::Terminal()
{

}

void ribi::maziak::Terminal::DoDisplay(const MainDialog& main_dialog)
{
  if (GetGameState() == GameState::has_won)
  {
    std::cout << "You won the game" << '\n';
    return;
  }
  else if (GetGameState() == GameState::game_over)
  {
    std::cout << "GAME OVER" << '\n';
    return;
  }

  TextCanvas canvas(11,11);
  const int view_height = 11;
  const int view_width = 11;
  //Draw maze
  {
    for (int y=0; y!=view_height; ++y)
    {
      for (int x=0; x!=view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = main_dialog.GetX() - (view_width  / 2) + x;
        const int yVector = main_dialog.GetY() - (view_height / 2) + y;
        //Draw the floor tile
        const char pixmap_floor {
          Sprites::ToChar(
            main_dialog.GetSpriteFloor(
              main_dialog.GetMaze(),
              xVector,
              yVector,
              main_dialog.GetDoShowSolution(),
              main_dialog.GetSolution()
            )
          )
        };
        canvas.PutChar(x,y,pixmap_floor);
        //Draw what's moving or standing on the floor
        const Sprite sprite_above_floor {
          main_dialog.GetSpriteAboveFloor(xVector,yVector,main_dialog.GetMaze())
        };
        if (sprite_above_floor != Sprite::transparent)
        {
          const char pixmap_above_floor {
            Sprites::ToChar(sprite_above_floor)
          };
          canvas.PutChar(x,y,pixmap_above_floor);
        }
      }
    }
  }

  //Draw player
  {
    const char player {
      Sprites::ToChar(
        main_dialog.GetSpritePlayer(
          main_dialog.GetPlayerDirection(),
          main_dialog.GetPlayerMove(),
          main_dialog.GetPlayerHasSword(),
          main_dialog.GetPlayerFightingFrame()
        )
      )
    };
    assert(player);
    canvas.PutChar(view_width/2,view_height / 2,player);
  }
  std::cout << canvas << '\n';
}
