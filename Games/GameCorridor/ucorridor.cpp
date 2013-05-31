/***************************************************************************
 *   SDL implementation of Quoridor game                                   *
 *   Copyright (C) 2007 by Or Dvory                                        *
 *   gnudles@nana.co.il                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <string>
#include <stdio.h>
#include <QFile>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#define status_text_color RGBAcolor(255,188,72,0)
#define status_down_color RGBtoInt(220,55,15)
#define status_up_color RGBtoInt(255,198,120)
#define button_down_color RGBtoInt(255,70,0)
#define button_up_color RGBtoInt(255,200,0)
#define button_text_color RGBAcolor(240,250,215,0)
#define SCRX 800
#define SCRY 600

const int margins=8;
const int squaresize=32;

inline void putpixel(int x, int y, int color);

inline int RGBtoInt(Uint8 r, Uint8 g, Uint8 b);

inline void draw_square(unsigned short x,unsigned short y,unsigned short width,unsigned short height, int color);

inline void draw_linex(unsigned short x,unsigned short y,unsigned short width,unsigned short height, int color);

inline Uint8 InttoR(int color);

inline Uint8 InttoG(int color);

inline Uint8 InttoB(int color);

inline void grad_square(unsigned short x,unsigned short y,unsigned short width,unsigned short height, int color1,int color2);

inline SDL_Color RGBAcolor(Uint16 r,Uint16 g,Uint16 b,Uint16 a);



SDL_Surface *load_image( std::string filename );


SDL_Surface *screen ;

unsigned int *pixptr;

TTF_Font *font;


void programexit()
{
	SDL_Quit();
	TTF_CloseFont( font );
	TTF_Quit();
}


class Textbar
{
	SDL_Rect text_bar;
	void draw_textarea(){
		grad_square(0, 0,SCRX,40,status_down_color, status_up_color);
	}
	public:
		bool mouse_over;
		Textbar()
		{
			text_bar.x=20;
			text_bar.y=10;
      font = TTF_OpenFont("resources/FreeSansBold.ttf", 22 );
			change_text("Welcome to Corridor");
		}
		void change_text(std::string new_text)
		{
				draw_textarea();
				SDL_Surface *sText;
        sText = TTF_RenderText_Blended( font, new_text.c_str(),status_text_color );
				SDL_BlitSurface( sText,NULL, screen,&text_bar );
				SDL_FreeSurface( sText );
				
				SDL_UpdateRect(screen, 0, 0, SCRX, 40);
		}
	
};

class Menu
{
	Uint16 lastmove;
	bool fullscreen;
	public:
		Menu()
		{
			lastmove=0;
			fullscreen=false;
			draw_menu();	
		}
		void notover()
		{
			lastmove=0;
		}
		Uint16 click_event(int y,Textbar *actiontext)
		{
			y-=42;
			y/=80;
			y++;
			switch(y)
			{
				case 1:
					return 3;
				case 2:
					changefullscreen();
					return 2;
				case 3:
					if (fullscreen)
						actiontext->change_text("I mustn't open links in full screen mode...");
					else
            //EDIT BY BILDERBIKKEL
            //system ("firefox gnudles.wmn.cc/corridor/howto.html");
            system ("firefox resources/howto.html");
					break;
				case 4:
					if (fullscreen)
						actiontext->change_text("I mustn't open links in full screen mode...");
					else
            //EDIT BY BILDERBIKKEL
            //system ("firefox gnudles.wmn.cc/corridor/about.html");
            system ("firefox resources/about.html");
          break;
				case 5:
                     return 4;
				case 6:
					return 1;
			}
			return 0;
		}
		void changefullscreen()
		{
			if (!fullscreen)
			{
				screen = SDL_SetVideoMode(SCRX, SCRY, 32, SDL_SWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
				fullscreen=true;
			}
			else
			{
				screen = SDL_SetVideoMode(SCRX, SCRY, 32, SDL_SWSURFACE|SDL_DOUBLEBUF);
				fullscreen=false;
			}
			draw_menu();
		}
		void move_event(int y,Textbar *actiontext)
		{
			if (y==0)
			{
				lastmove=0;
				return;
			}
			y-=42;
			y/=80;
			y++;
			if (y!=lastmove)
				switch(y)
				{
					case 1:
						actiontext->change_text("Start New Game");
						break;
					case 2:
						actiontext->change_text("Toggle Full Screen");
						break;
					case 3:
						actiontext->change_text("Display Game Tutorial");
						break;
					case 4:
						actiontext->change_text("(C) 2007, Or Dvory, distributed under the terms of the GPLv2");
						break;
					case 5:
						actiontext->change_text("Undo last move");
						break;
					case 6:
						actiontext->change_text("Quit the program");
						break;
					
					default:
						actiontext->change_text("");
						y=0;
				}
			lastmove=y;
		}
		void draw_button(int y,std::string button_text){
			SDL_Rect text_label={20,y+30,0,0};
			grad_square(2, y,250,78,button_down_color,button_up_color );
			SDL_Surface *sText;
			sText = TTF_RenderText_Blended( font, button_text.c_str(),button_text_color );
			SDL_BlitSurface( sText,NULL, screen,&text_label );
			SDL_FreeSurface( sText );
		}
	void draw_menu(){
		draw_button(42,"New Game");
		draw_button(122,"Full Screen");
		draw_button(202,"How to Play");
		draw_button(282,"About");
		draw_button(362,"Undo");
		draw_button(442,"Exit");
	}
};
class Game
{
    typedef struct 
    {
         bool able;
         bool player;     
         char movex,movey;
         Uint8 wall_number;
    }movement;
    movement lmove;
	class Wall{
		
		
		public:

			Uint16 spx,spy;
			bool placed,vertical;
			void set_wall(Uint16 spx,Uint16 spy)
			{
				this->placed=false;
				this->vertical=true;
				this->spx=spx;
				this->spy=spy;
			}
			void set_focus()
			{
				draw_wall(RGBtoInt(200,70,50));
/*				if (spy==0)
					SDL_UpdateRect(screen, spx*(squaresize+margins)-margins+360,60,margins,margins+2*squaresize);
				else
					SDL_UpdateRect(screen,spx*(squaresize+margins)-margins+360,squaresize*2+60+spy*(squaresize+margins),margins,margins+2*squaresize);*/
			}
			void remove_focus()
			{
				draw_wall();
/*				if (spy==0)
					SDL_UpdateRect(screen, spx*(squaresize+margins)-margins+360,60,margins,margins+2*squaresize);
				else
					SDL_UpdateRect(screen,spx*(squaresize+margins)-margins+360,squaresize*11+60+9*margins,margins,margins+2*squaresize);*/
			}
			
			void draw_wall(int color)
			{
				if (spy==0)
				{
					draw_square(spx*(squaresize+margins)-margins+360,60,margins,margins+2*squaresize,color );
					SDL_UpdateRect(screen, spx*(squaresize+margins)-margins+360,60,margins,margins+2*squaresize);
				}
				else
				{
					if (spy==9)
					{
						draw_square(spx*(squaresize+margins)-margins+360, squaresize*11+60+9*margins,margins,margins+2*squaresize,color );
						SDL_UpdateRect(screen,spx*(squaresize+margins)-margins+360,squaresize*2+60+spy*(squaresize+margins),margins,margins+2*squaresize);
					}
					else
					{
					if (vertical)
					{
						draw_square(spx*(squaresize+margins)-margins+360, squaresize+60+spy*(squaresize+margins),margins,margins+2*squaresize,color );
						SDL_UpdateRect(screen,spx*(squaresize+margins)-margins+360,squaresize+60+spy*(squaresize+margins),margins,margins+2*squaresize);
						
					}
					else
					{
						draw_square(spx*(squaresize+margins)+360, squaresize*2+60+spy*(squaresize+margins),margins+2*squaresize,margins,color );
						SDL_UpdateRect(screen,spx*(squaresize+margins)+360,squaresize*2+60+spy*(squaresize+margins),margins+2*squaresize,margins);
					}
					}
				}
			}
			void draw_wall()
			{
				draw_wall(RGBtoInt(140,30,10));
			}
			void changepos(Uint16 spx,Uint16 spy,bool vertical,movement *lmove)
			{
				draw_wall(RGBtoInt(190,130,60));
				(*lmove).player=false;
				(*lmove).able=true;
				(*lmove).wall_number=this->spx;
				this->spx=spx;
				this->spy=spy;
				this->vertical=vertical;
				this->placed=true;
				draw_wall();
			}
	};
	class Player{
		SDL_Surface *playerlook,*playerlooksel;
		SDL_Rect entrypoint;
		
		public:
			Wall walls[10];
			char desty,locx,locy, wselected;//wselected -1 none, 0-9 blocks, 10 pawn
			bool mouse_over;
			void reset_player()
			{
				mouse_over=false;
				locy=10-desty;
				wselected=-1;
				locx=5;
				entrypoint.x=360+4*margins+4*squaresize;
				entrypoint.y=squaresize+60+locy*(squaresize+margins);
			}
			Player(Uint16 sy){
				desty=10-sy;
				reset_player();
				if (sy==9)
				{
					playerlook=load_image( "resources//indx_crimson.png" );
					playerlooksel=load_image( "resources//sel_indx_crimson.png" );
				}
				else if (sy==1)
				{
					playerlook=load_image( "resources//indx_fawn.png" );
					playerlooksel=load_image( "resources//sel_indx_fawn.png" );
				}
			}

			
			~Player()
			{
				SDL_FreeSurface( playerlook );
				SDL_FreeSurface( playerlooksel );
			}
			bool can_up(Player *enemy)
			{
				for(Uint16 i=0;i<10;i++)
					if ((!enemy->walls[i].vertical) && enemy->walls[i].placed)
						if(enemy->walls[i].spy+1==this->locy)
							if (this->locx-1==enemy->walls[i].spx || this->locx-2==enemy->walls[i].spx)
							return false;
				for(Uint16 i=0;i<10;i++)
					if ((!this->walls[i].vertical) && this->walls[i].placed)
						if(this->walls[i].spy+1==this->locy)
							if (this->locx-1==this->walls[i].spx || this->locx-2==this->walls[i].spx)
								return false;
				if (locy-1>0)
					return true;
				return false;
			}
			bool can_left(Player *enemy)
			{
				for(Uint16 i=0;i<10;i++)
					if ((enemy->walls[i].vertical) && enemy->walls[i].placed)
						if(enemy->walls[i].spx+1==this->locx)
							if (this->locy-1==enemy->walls[i].spy || this->locy==enemy->walls[i].spy)
								return false;
				for(Uint16 i=0;i<10;i++)
					if ((this->walls[i].vertical) && this->walls[i].placed)
						if(this->walls[i].spx+1==this->locx)
							if (this->locy-1==this->walls[i].spy || this->locy==this->walls[i].spy)
								return false;
				if (locx-1>0)
					return true;
				return false;
			}
			bool can_down(Player *enemy)
			{
				for(Uint16 i=0;i<10;i++)
					if ((!enemy->walls[i].vertical) && enemy->walls[i].placed)
						if(enemy->walls[i].spy==this->locy)
							if (this->locx-1==enemy->walls[i].spx || this->locx-2==enemy->walls[i].spx)
								return false;
				for(Uint16 i=0;i<10;i++)
					if ((!this->walls[i].vertical) && this->walls[i].placed)
						if(this->walls[i].spy==this->locy)
							if (this->locx-1==this->walls[i].spx || this->locx-2==this->walls[i].spx)
								return false;
				if (locy+1<10)
					return true;
				return false;
			}
			bool can_right(Player *enemy)
			{
				for(Uint16 i=0;i<10;i++)
					if ((enemy->walls[i].vertical) && enemy->walls[i].placed)
						if(enemy->walls[i].spx==this->locx)
							if (this->locy-1==enemy->walls[i].spy || this->locy==enemy->walls[i].spy)
								return false;
				for(Uint16 i=0;i<10;i++)
					if ((this->walls[i].vertical) && this->walls[i].placed)
						if(this->walls[i].spx==this->locx)
							if (this->locy-1==this->walls[i].spy || this->locy==this->walls[i].spy)
								return false;
				if (locx+1<10)
					return true;
				return false;
			}
			void select(Player *enemy)
			{
				if (wselected>=0 && wselected<10)
				{
					walls[wselected].remove_focus();
					wselected=-1;
				}
				wselected=9-wselected;
				draw_player();
				
				if (wselected==10){
					make_around(enemy);
				}
				else{
					del_around(enemy);
				}
				SDL_UpdateRect(screen, 0, 0, SCRX, SCRY);
			}
			void make_around(Player *enemy)
			{
				SDL_SetAlpha(playerlooksel, SDL_RLEACCEL|SDL_SRCALPHA, 80);
				if (can_left(enemy))
				{
					if (enemy->locx+1==this->locx && enemy->locy==this->locy)
					{
						if (enemy->can_left(this))
						{
							entrypoint.x=(locx-3)*(squaresize+margins)+360;
							entrypoint.y=squaresize+60+(locy)*(squaresize+margins);
							draw_player();
						}
						else
						{
							if (enemy->can_up(this))
							{
								entrypoint.x=(locx-2)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy-1)*(squaresize+margins);
								draw_player();
							}
							if (enemy->can_down(this))
							{
								entrypoint.x=(locx-2)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy+1)*(squaresize+margins);
								draw_player();
							}
						}
					}
					else
					{
						entrypoint.y=squaresize+60+(locy)*(squaresize+margins);
						entrypoint.x=(locx-2)*(squaresize+margins)+360;
						draw_player();
					}
				}
				if (can_right(enemy))
				{
					if (enemy->locx-1==this->locx && enemy->locy==this->locy)
					{
						if (enemy->can_right(this))
						{
							entrypoint.x=(locx+1)*(squaresize+margins)+360;
							entrypoint.y=squaresize+60+(locy)*(squaresize+margins);
							draw_player();
						}
						else
						{
							if (enemy->can_up(this))
							{
								entrypoint.x=(locx)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy-1)*(squaresize+margins);
								draw_player();
							}
							if (enemy->can_down(this))
							{
								entrypoint.x=(locx)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy+1)*(squaresize+margins);
								draw_player();
							}
						}
					}
					else
					{
						entrypoint.y=squaresize+60+(locy)*(squaresize+margins);
						entrypoint.x=(locx)*(squaresize+margins)+360;
						draw_player();
					}
				}
				if (can_up(enemy))
				{
					if (enemy->locx==this->locx && enemy->locy==this->locy-1)
					{
						if (enemy->can_up(this))
						{
							entrypoint.x=(locx-1)*(squaresize+margins)+360;
							entrypoint.y=squaresize+60+(locy-2)*(squaresize+margins);
							draw_player();
						}
						else
						{
							if (enemy->can_right(this))
							{
								entrypoint.x=(locx)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy-1)*(squaresize+margins);
								draw_player();
							}
							if (enemy->can_left(this))
							{
								entrypoint.x=(locx-2)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy-1)*(squaresize+margins);
								draw_player();
							}
						}
					}
					else
					{
						entrypoint.x=(locx-1)*(squaresize+margins)+360;
						entrypoint.y=squaresize+60+(locy-1)*(squaresize+margins);
						draw_player();
					}
				}
				if (can_down(enemy))
				{
					if (enemy->locx==this->locx && enemy->locy-1==this->locy)
					{
						if (enemy->can_down(this))
						{
							entrypoint.x=(locx-1)*(squaresize+margins)+360;
							entrypoint.y=squaresize+60+(locy+2)*(squaresize+margins);
							draw_player();
						}
						else
						{
							if (enemy->can_right(this))
							{
								entrypoint.x=(locx)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy+1)*(squaresize+margins);
								draw_player();
							}
							if (enemy->can_left(this))
							{
								entrypoint.x=(locx-2)*(squaresize+margins)+360;
								entrypoint.y=squaresize+60+(locy+1)*(squaresize+margins);
								draw_player();
							}
						}
					}
					else
					{
						entrypoint.x=(locx-1)*(squaresize+margins)+360;
						entrypoint.y=squaresize+60+(locy+1)*(squaresize+margins);
						draw_player();
					}
				}
				entrypoint.x=(locx-1)*(squaresize+margins)+360;
				entrypoint.y=squaresize+60+locy*(squaresize+margins);
					
				SDL_SetAlpha(playerlooksel, SDL_RLEACCEL|SDL_SRCALPHA, 255);
			}
			void del_around(Player *enemy)
			{
				if (can_left(enemy))
				{
					if (enemy->locx+1==this->locx && enemy->locy==this->locy)
					{
						if (enemy->can_left(this))
						{
							draw_square((locx-3)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-1)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
						}
						else
						{
							if (enemy->can_up(this))
							{
								draw_square((locx-2)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-2)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
							if (enemy->can_down(this))
							{
								draw_square((locx-2)*(squaresize+margins)+360, squaresize*2+margins+60+(locy)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
						}
					}
					else
					{
						draw_square((locx-2)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-1)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
					}
				}
				if (can_right(enemy))
				{
					if (enemy->locx-1==this->locx && enemy->locy==this->locy)
					{
						if (enemy->can_right(this))
						{
							draw_square((locx+1)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-1)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
						}
						else
						{
							if (enemy->can_up(this))
							{
								draw_square((locx)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-2)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
							if (enemy->can_down(this))
							{
								draw_square((locx)*(squaresize+margins)+360, squaresize*2+margins+60+(locy)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
						}
					}
					else
					{
						draw_square((locx)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-1)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
					}
				}
				if (can_up(enemy))
				{
					if (enemy->locx==this->locx && enemy->locy==this->locy-1)
					{
						if (enemy->can_up(this))
						{
							draw_square((locx-1)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-3)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
						}
						else
						{
							if (enemy->can_right(this))
							{
								draw_square((locx)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-2)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
							if (enemy->can_left(this))
							{
								draw_square((locx-2)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-2)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
						}
					}
					else
					{
						draw_square((locx-1)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-2)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
					}
				}
				if (can_down(enemy))
				{
					if (enemy->locx==this->locx && enemy->locy-1==this->locy)
					{
						if (enemy->can_down(this))
						{
							draw_square((locx-1)*(squaresize+margins)+360, squaresize*2+margins+60+(locy+1)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
						}
						else
						{
							if (enemy->can_right(this))
							{
								draw_square((locx)*(squaresize+margins)+360, squaresize*2+margins+60+(locy)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
							if (enemy->can_left(this))
							{
								draw_square((locx-2)*(squaresize+margins)+360, squaresize*2+margins+60+(locy)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
							}
						}
					}
					else
					{
						draw_square((locx-1)*(squaresize+margins)+360, squaresize*2+margins+60+(locy)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
					}
				}
			}
			void draw_player()
			{
				if (wselected==10)
					SDL_BlitSurface( playerlooksel,NULL, screen,&entrypoint );
				else
					SDL_BlitSurface( playerlook,NULL, screen,&entrypoint );
			}
			bool onplayer(Uint16 x,Uint16 y)
			{
				if (x>(entrypoint.x) && x<(entrypoint.x+squaresize))
					if (y>(entrypoint.y) && y<(entrypoint.y+squaresize))
						return true;
				return false;
			}
			bool onsquare(Uint16 x,Uint16 y,Uint16 bx,Uint16 by)
			{
				if (x>bx && x<bx+squaresize)
					if (y>by && y<by+squaresize)
						return true;
				return false;
			}
			char possible_move(Uint16 x,Uint16 y,Player *enemy,movement *lmove)
			{
				//up
				if (can_up(enemy))
				{
					if (enemy->locx==this->locx && enemy->locy==this->locy-1)
					{
						if (enemy->can_up(this))
						{
							if (onsquare( x, y,(locx-1)*(squaresize+margins)+360,squaresize+60+(locy-2)*(squaresize+margins)))
							{
								return move(0,-2,lmove);
							}
						}
						else
						{
							if (enemy->can_right(this))
							{
								if (onsquare( x, y,(locx)*(squaresize+margins)+360,squaresize+60+(locy-1)*(squaresize+margins)))
								{
									return move(1,-1,lmove);
								}
							}
							if (enemy->can_left(this))
							{
								if (onsquare( x, y,(locx-2)*(squaresize+margins)+360,squaresize+60+(locy-1)*(squaresize+margins)))
								{
									return move(-1,-1,lmove);
								}
							}
						}
					}
					else
					{
						if (onsquare( x, y,(locx-1)*(squaresize+margins)+360,squaresize+60+(locy-1)*(squaresize+margins)))
						{
							return move(0,-1,lmove);
						}
					}
				}

				//left
				if (can_left(enemy))
				{
					if (enemy->locx+1==this->locx && enemy->locy==this->locy)
					{
						if (enemy->can_left(this))
						{
							if (onsquare( x, y,(locx-3)*(squaresize+margins)+360,squaresize+60+(locy)*(squaresize+margins)))
							{
								return move(-2,0,lmove);
							}
						}
						else
						{
							if (enemy->can_up(this))
							{
								if (onsquare( x, y,(locx-2)*(squaresize+margins)+360,squaresize+60+(locy-1)*(squaresize+margins)))
								{
									return move(-1,-1,lmove);
								}
							}
							if (enemy->can_down(this))
							{
								if (onsquare( x, y,(locx-2)*(squaresize+margins)+360,squaresize+60+(locy+1)*(squaresize+margins)))
								{
									return move(-1,1,lmove);
								}
							}
						}
					}
					else
					{
						if (onsquare( x, y,(locx-2)*(squaresize+margins)+360,squaresize+60+(locy)*(squaresize+margins)))
						{
							return move(-1,0,lmove);
						}
					}
				}
				//right
				if (can_right(enemy))
				{
					if (enemy->locx-1==this->locx && enemy->locy==this->locy)
					{
						if (enemy->can_right(this))
						{
							if (onsquare( x, y,(locx+1)*(squaresize+margins)+360,squaresize+60+(locy)*(squaresize+margins)))
							{
								return move(2,0,lmove);
							}
						}
						else
						{
							if (enemy->can_up(this))
							{
								if (onsquare( x, y,(locx)*(squaresize+margins)+360,squaresize+60+(locy-1)*(squaresize+margins)))
								{
									return move(1,-1,lmove);
								}
							}
							if (enemy->can_down(this))
							{
								if (onsquare( x, y,(locx)*(squaresize+margins)+360,squaresize+60+(locy+1)*(squaresize+margins)))
								{
									return move(1,1,lmove);
								}
							}
						}
					}
					else
					{
						if (onsquare( x, y,(locx)*(squaresize+margins)+360,squaresize+60+(locy)*(squaresize+margins)))
						{
							return move(1,0,lmove);
						}
					}
				}
				//down
				if (can_down(enemy))
				{
					if (enemy->locx==this->locx && enemy->locy-1==this->locy)
					{
						if (enemy->can_down(this))
						{
							if (onsquare( x, y,(locx-1)*(squaresize+margins)+360,squaresize+60+(locy+2)*(squaresize+margins)))
							{
								return move(0,2,lmove);
							}
						}
						else
						{
							if (enemy->can_right(this))
							{
								if (onsquare( x, y,(locx)*(squaresize+margins)+360,squaresize+60+(locy+1)*(squaresize+margins)))
								{
									return move(1,1,lmove);
								}
							}
							if (enemy->can_left(this))
							{
								if (onsquare( x, y,(locx-2)*(squaresize+margins)+360,squaresize+60+(locy+1)*(squaresize+margins)))
								{
									return move(-1,1,lmove);
								}
							}
						}
					}
					else
					{
						if (onsquare( x, y,(locx-1)*(squaresize+margins)+360,squaresize+60+(locy+1)*(squaresize+margins)))
						{
							return move(0,1,lmove);
						}
					}
				}
				return 0;
			}

			char move(char addx,char addy,movement *lmove)
			{
				draw_square((locx-1)*(squaresize+margins)+360, squaresize*2+margins+60+(locy-1)*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
				locx+=addx;
				locy+=addy;
				(*lmove).movex=-addx;
				(*lmove).movey=-addy;
				(*lmove).able=true;
				(*lmove).player=true;
				entrypoint.x=(locx-1)*(squaresize+margins)+360;
				entrypoint.y=squaresize+60+locy*(squaresize+margins);
				draw_player();
				wselected=-1;
				if (locy==desty)//game end
					return -1;
				return 1;
			}
	};
	Wall demo;
	bool wall_posible(Uint16 spx,Uint16 spy,bool vertical)
	{
		for(Uint16 i=0;i<10;i++)
			if (fawn->walls[i].placed)
			{
				if (fawn->walls[i].vertical==vertical)//over
				{
					if (fawn->walls[i].spy==spy && fawn->walls[i].spx==spx)//same location
						return false;
					if (fawn->walls[i].spx==spx && vertical)
					{
						if (fawn->walls[i].spy==spy-1 || fawn->walls[i].spy==spy+1)
							return false;
					}
					else
					{
						if (fawn->walls[i].spx==spx+1 || fawn->walls[i].spx==spx-1)
							if (fawn->walls[i].spy==spy && (!vertical))
								return false;
					}
				}
				else //cross
				{
					if(fawn->walls[i].vertical && fawn->walls[i].spx==spx+1 && fawn->walls[i].spy==spy)
						return false;
					if(vertical && spx==fawn->walls[i].spx+1 && spy==fawn->walls[i].spy)
						return false;
				}
			}
		for(Uint16 i=0;i<10;i++)
			if (crimson->walls[i].placed)
			{
				if (crimson->walls[i].vertical==vertical)
				{
					if (crimson->walls[i].spy==spy && crimson->walls[i].spx==spx)
						return false;
					if (crimson->walls[i].spx==spx && vertical)
					{
						if (crimson->walls[i].spy==spy-1 || crimson->walls[i].spy==spy+1)
							return false;
					}
					else
					{
						if (crimson->walls[i].spx==spx+1 || crimson->walls[i].spx==spx-1)
							if (crimson->walls[i].spy==spy && (!vertical))
								return false;
					}
				}
				else
				{
					if(crimson->walls[i].vertical && crimson->walls[i].spx==spx+1 && crimson->walls[i].spy==spy)
						return false;
					if(vertical && spx==crimson->walls[i].spx+1 && spy==crimson->walls[i].spy)
						return false;
				}
			}
		return true;
	}
	void change_wall_place(Uint16 mx,Uint16 my,Wall *swall){
		
		if (demo.spy!=0)
		{
		swall->changepos(demo.spx,demo.spy,demo.vertical,&lmove);
		if (turn)
		{
			crimson->wselected=-1;
			change_turn();
		}
		else
		{
			fawn->wselected=-1;
			change_turn();
		}
		demo.spy=0;
		}
		
	}
	void preview_wall_place(Uint16 mx,Uint16 my){
		Wall temp=demo;
		if (wall_place(mx,my,&(demo.spx),&(demo.spy),&(demo.vertical)))
		{
			if (!(temp.spx==demo.spx && temp.spy==demo.spy && temp.vertical==demo.vertical ))
			{
				if (temp.spy!=0)
					temp.draw_wall(RGBtoInt(190,130,60));
				demo.draw_wall(RGBtoInt(230,110,50));
			}
		}
		else
		{
			demo.spy=0;//can't put the wall there
			if (temp.spy!=0)
				temp.draw_wall(RGBtoInt(190,130,60));
		}
	}
	bool wall_place(Uint16 mx,Uint16 my,Uint16 *spx,Uint16 *spy,bool *vertical)
	{
		//spx*(squaresize+margins)-margins+360, squaresize*2+60+spy*(squaresize+margins),margins,margins+2*squaresize
		mx+=margins-360;
		*spx=mx/(squaresize+margins);
		mx%=(squaresize+margins);
		
		my-=squaresize*2;
		my-=60;
		//my-=2*margins;
		*spy=my/(squaresize+margins) +1;
		my%=(squaresize+margins);
		if (my<margins)
		{
			if (mx>=margins)
			{
				*vertical=false;
				*spy-=1;
				if (mx<margins+squaresize/2)
					if (*spx>0)
					*spx-=1;
			}
			else if (*vertical) *spy-=1;
				else { *spx-=1;
					*spy-=1;
				}
		}
		else
			if (mx<margins)
			{
			*vertical=true;
			if (my<margins+squaresize/2)
				if (*spy>1)
				*spy-=1;
			}
			else return false;
		if (!wall_posible((*spx),(*spy),(*vertical))) // over existing block or implaceable
			return false;
		if (*vertical)
		{
			if ((*spx)>0 && (*spx)<=8 && (*spy)>0 && (*spy)<=8)
				return true;
		}
		else 
		{
			if (((*spx)<8) && ((*spy)>0) && ((*spy)<=8))
				return true;
		}
		return false;
	}
    void change_turn()
    {
         turn=!turn;
         lmove.able=true;
    }
	Player *fawn,*crimson;
	public:
		bool turn,game_end;//crimson - true, fawn - false
		Game()
		{
			reset_game_status();
			fawn=new Player(1);
			crimson=new Player(9);
			set_walls();
			draw_board();
			demo.set_wall(1,0);
		}
		void reset_game_status()
		{
            lmove.able=false;
			game_end=false;
			turn = true;
		}
		void new_game()
		{
			reset_game_status();
			reset_players();
			set_walls();
			draw_board();
			demo.set_wall(1,0);
		}
		void reset_players()
		{
			fawn->reset_player();
			crimson->reset_player();
		}
		void set_walls()
		{			
			for(Uint16 i=0;i<10;i++)
				fawn->walls[i].set_wall(i,0);
			for(Uint16 i=0;i<10;i++)
				crimson->walls[i].set_wall(i,9);
		}
		void draw_board()
		{
			Uint8 i,j;
			for (j=0;j<9;j++)
				for (i=0;i<9;i++)
					draw_square(i*(squaresize+margins)+360, squaresize*2+margins+60+j*(squaresize+margins),squaresize,squaresize,RGBtoInt(230,170,100) );
			for (i=0;i<10;i++)
				draw_square(i*(squaresize+margins)+360-margins, squaresize*2+margins+60,margins,squaresize*9+margins*8,RGBtoInt(190,130,60) );
			for (i=0;i<8;i++)
				draw_square(360, i*(squaresize+margins)+squaresize*3+margins+60,squaresize*9+margins*8,margins,RGBtoInt(190,130,60) );
			draw_square(360-margins,60,squaresize*9+margins*10,squaresize*2+margins,RGBtoInt(190,130,60) );
			draw_square(360-margins,60+squaresize*11+margins*9,squaresize*9+margins*10,squaresize*2+margins,RGBtoInt(190,130,60) );
			for( i=0;i<10;i++)
				fawn->walls[i].draw_wall();
			for( i=0;i<10;i++)
				crimson->walls[i].draw_wall();
			crimson->draw_player();
			fawn->draw_player();
			if (crimson->wselected==10)
				crimson->make_around(fawn);
			else if (fawn->wselected==10)
				fawn->make_around(crimson);
			
			SDL_UpdateRect(screen, 0, 0, SCRX, SCRY);
		}
		char which_wall(Uint16 x,bool turn)
		{
			x+=margins-360;
			char spx=x/(squaresize+margins);
			x%=(squaresize+margins);
			if (x<margins && spx>=0 && spx<=9)
				if (turn)
				{
					if (!crimson->walls[spx].placed)
						return spx;
				}
				else if (!fawn->walls[spx].placed)
						return spx;
			return -1;
		}
		void undo()
		{
			if (lmove.able && (!game_end))
			{
				turn=!turn;
				if (lmove.player)
				{
					if (turn)
						crimson->move(lmove.movex,lmove.movey,&lmove);
					else
						fawn->move(lmove.movex,lmove.movey,&lmove);
				}
				else
				{
                    if (turn)
                    {
                       crimson->walls[lmove.wall_number].draw_wall(RGBtoInt(190,130,60));
                       crimson->walls[lmove.wall_number].set_wall(lmove.wall_number,9);
                       crimson->walls[lmove.wall_number].draw_wall();
                    }
                    else
                    {
                       fawn->walls[lmove.wall_number].draw_wall(RGBtoInt(190,130,60));
                       fawn->walls[lmove.wall_number].set_wall(lmove.wall_number,0);
                       fawn->walls[lmove.wall_number].draw_wall();
                    }
                }
				SDL_UpdateRect(screen, 0, 0, SCRX, SCRY);
				lmove.able=false;
			}
		}
		void move_event(Uint16 x, Uint16 y,Textbar *actiontext)
		{
			if(!game_end)
			{
				if (turn)
				{
					if (crimson->onplayer(x,y)&& !(crimson->mouse_over))
					{
						
						if (crimson->wselected!=10)
						{
							actiontext->change_text("Player 1: Select your crimson Pawn");
							crimson->mouse_over=true;
						}
					}
					
					else
					{
						if (!crimson->onplayer(x,y) && (crimson->mouse_over))
						{
								crimson->mouse_over=false;
								actiontext->change_text("");
						}
						if (crimson->wselected >=0 && crimson->wselected<10)
							preview_wall_place(x,y);
						
					}
				}
				else 
					if (fawn->onplayer(x,y)&& !(fawn->mouse_over))
					{
						if (fawn->wselected!=10)
						{
						actiontext->change_text("Player 2: Select your fawn Pawn");
						fawn->mouse_over=true;
						}
					}
					else
					{
						if ((!fawn->onplayer(x,y)) && (fawn->mouse_over))
						{
							fawn->mouse_over=false;
							actiontext->change_text("");
							
						}
						if (fawn->wselected >=0 && fawn->wselected<10)
								preview_wall_place(x,y);
						
					}
			}
		}
		
		
		void click_event(Uint16 button,Uint16 x, Uint16 y,Textbar *actiontext)
		{
			//walls[0][0].changepos(4,2,false);
			char other_lx,other_ly;
			if(!game_end)
			if (turn)
			{
				other_lx=fawn->locx;
				other_ly=fawn->locy;
				if (crimson->onplayer(x,y))
					crimson->select(fawn);
				else 
				{
					if(crimson->wselected==10)
					{
						crimson->select(fawn);
						char possible=crimson->possible_move(x,y,fawn,&lmove);
						if (possible==-1)
						{
								game_end=true;
								actiontext->change_text("Game won by Player 1 with his crimson Pawn");
						}
						else if (possible !=0)
							change_turn();
					}
					else
					{
						if (crimson->wselected>=0 && crimson->wselected<10)
						{
							change_wall_place(x,y,&(crimson->walls[crimson->wselected]));
						}
						else
						if (y>=60+11*squaresize+9*margins && y<60+13*squaresize+10*margins)
						{
							char spx=which_wall(x,turn);
							if (spx<0)
								return;
							if (crimson->wselected!=spx && crimson->wselected>=0 && crimson->wselected<10)
								crimson->walls[crimson->wselected].remove_focus();
							crimson->wselected=spx;
							crimson->walls[spx].set_focus();
						}
					}
				}
			}
			else
			{
				if (fawn->onplayer(x,y))
					fawn->select(crimson);
				else 
				{
					if(fawn->wselected==10)
					{
						fawn->select(crimson);
						char possible;
						possible=fawn->possible_move(x,y,crimson,&lmove);
						if (possible==-1)
						{
								game_end=true;
								actiontext->change_text("Game won by Player 2 with his fawn Pawn");
						}
						else if (possible !=0)
							change_turn();
					}
					else
					{
						if (fawn->wselected>=0 && fawn->wselected<10)
						{
							change_wall_place(x,y,&(fawn->walls[fawn->wselected]));
						}
						else
							if (y>=60 && y<60+2*squaresize+margins)
							{
								char spx=which_wall(x,turn);
								if (spx<0)
									return;
								if (fawn->wselected!=spx && fawn->wselected>=0 && fawn->wselected<10)
									fawn->walls[fawn->wselected].remove_focus();
								fawn->wselected=spx;
								fawn->walls[spx].set_focus();
							}
					}
					
				}
			}
			SDL_UpdateRect(screen, 0, 0, SCRX, SCRY);
		}

};

int main(int argc, char *argv[])
{
	atexit(programexit);
  if ( SDL_Init(SDL_INIT_VIDEO |SDL_INIT_AUDIO) < 0 ) 

	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	  exit(1);
  }

	// Attempt to create a 800x600 window with 32bit pixels.
	screen = SDL_SetVideoMode(SCRX, SCRY, 32, SDL_SWSURFACE|SDL_DOUBLEBUF);
			  // If we fail, return error.
			if ( screen == NULL )
			{
				fprintf(stderr, "Unable to set 800x600 video: %s\n", SDL_GetError());
				exit(1);
			}
	pixptr = (unsigned int*)screen->pixels;
	TTF_Init();
	SDL_WM_SetCaption( "Quoridor Game",NULL);
	SDL_Surface *icon=IMG_Load("resources//corridor.png");
	SDL_WM_SetIcon(icon, NULL);
	SDL_FreeSurface(icon);
	SDL_UnlockSurface(screen);
  Textbar * actiontext= new Textbar();
	Game *main_game= new Game();
	Menu *main_menu= new Menu();
	Uint16 menucevt;
	
	SDL_UpdateRect(screen, 2, 0, 250, SCRY);
	bool move_event_menu=false;
	while (1)
	{
		SDL_Delay(16);
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_MOUSEBUTTONUP:
					//SDL_UnlockSurface(screen);
					if(event.button.y>=42)
					{
						if (event.button.x<254)
						{
							if (event.button.button==1)
							{
								menucevt=main_menu->click_event(event.button.y,actiontext);
								switch (menucevt)
								{
                                case 4:
                                    main_game->undo();
                                    break;
								case 1:
									goto quit;
								case 2:
									main_game->draw_board();
									SDL_UpdateRect(screen, 0, 0, SCRX, SCRY);
									break;
								case 3:
									main_game->new_game();
									break;
								}
							}
						}
						else
						{
							main_game->click_event(event.button.button,event.button.x,event.button.y,actiontext);
						}
					}
					else 
					{
						if (!main_game->game_end)
							if (main_game->turn)
								actiontext->change_text("It's the crimson turn (Player 1)");
							else
								actiontext->change_text("It's the fawn turn (Player 2)");
						else
							if (main_game->turn)
								actiontext->change_text("crimson (Player 1) won the game!");
							else 
								actiontext->change_text("fawn (Player 2) won the game!");
					}
					//SDL_LockSurface(screen);
					break;
				case SDL_MOUSEMOTION:
					//SDL_UnlockSurface(screen);
					if(event.motion.y>=42)
					{
						if (actiontext->mouse_over)
							actiontext->mouse_over=false;
						if (event.motion.x<254)
						{
							main_menu->move_event(event.motion.y,actiontext);
							move_event_menu=true;
						}
						else
						{
							if (move_event_menu)
							{
								main_menu->notover();
								actiontext->change_text("");
								move_event_menu=false;
							}
							main_game->move_event(event.motion.x,event.motion.y,actiontext);
							
						}
					}
					else 
					{
						main_menu->notover();
						if (!actiontext->mouse_over)
							actiontext->change_text("Welcome to Corridor");
						actiontext->mouse_over=true;
					}
					//SDL_LockSurface(screen);
					break;
				case SDL_QUIT:
					quit:
					delete main_game;
					delete main_menu;
					delete actiontext;
					return(0);
			}
		}
	}
	return 0;
}
 

inline void draw_linex(unsigned short x,unsigned short ly,unsigned short width, int color)
{
	unsigned short lx=x+width;
	while (lx>x)
	{
		lx--;
		putpixel(lx,ly,color);
	}
}

inline void draw_square(unsigned short x,unsigned short y,unsigned short width,unsigned short height, int color)
{

	
	unsigned short ly=y+height;

	
		while (ly>y)
		{
			ly--;
			draw_linex(x,ly,width,color);
		}
	
	
}
void grad_square(unsigned short x,unsigned short y,unsigned short width,unsigned short height, int color1,int color2)
{

	
	unsigned short ly=y+height;
	char r=char((InttoR(color2)-InttoR(color1))/(float)(height)-0.1),g=char((InttoG(color2)-InttoG(color1))/(float)(height)-0.1),b=char((InttoB(color2)-InttoB(color1))/(float)(height)-0.1);

	
	while (ly>y)
	{
		ly--;
		draw_linex(x,ly,width,color1);
		color1=RGBtoInt(InttoR(color1)+r, InttoG(color1)+g, InttoB(color1)+b);
	}
	
	
}

inline int RGBtoInt(Uint8 r, Uint8 g, Uint8 b)
{
	return ((r<<16)|(g<<8)|b);
}
inline Uint8 InttoR(int color)
{
	return (color>>16);
}
inline Uint8 InttoG(int color)
{
	return (color>>8)%256;
}
inline Uint8 InttoB(int color)
{
	return (color)%256;
}

inline SDL_Color RGBAcolor(Uint16 r,Uint16 g,Uint16 b,Uint16 a)
{
SDL_Color clr={r,g,b,a};
return clr;
}

inline void putpixel(int x, int y, int color)
{
		int lineoffset = y * (screen->pitch / 4);
		pixptr[lineoffset + x] = color;
}

SDL_Surface *load_image( std::string filename ) 
{
    //The image that's loaded
	SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
    
    //Load the image using SDL_image
	loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
	if( loadedImage != NULL )
	{
		SDL_SetColorKey(loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB(loadedImage->format, 0, 0,0));
        //Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );

        
        //Free the old image
		SDL_FreeSurface( loadedImage );
	}
    
    //Return the optimized image
	return optimizedImage;
}

