#include "maziakterminal.h"

#include "textcanvas.h"
#include "maziakmaindialog.h"

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

  TextCanvas canvas(20,20);
  const int view_height = main_dialog.GetViewHeight();
  const int view_width = main_dialog.GetViewWidth();
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
            GetSpriteFloor(
              GetMaze(),
              xVector,
              yVector,
              GetDoShowSolution(),
              GetSolution()
            )
          )
        };
        canvas.PutChar(x,y,pixmap_floor);
        //Draw what's moving or standing on the floor
        const Sprite sprite_above_floor {
          GetSpriteAboveFloor(xVector,yVector,GetMaze())
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
        GetSpritePlayer(
          GetPlayerDirection(),
          GetPlayerMove(),
          GetPlayerHasSword(),
          GetPlayerFightingFrame()
        )
      )
    };
    assert(player);
    canvas.PutChar(view_width/2,view_height / 2,player);
  }
  return canvas;

}
