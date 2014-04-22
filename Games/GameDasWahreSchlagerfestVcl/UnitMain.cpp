//---------------------------------------------------------------------------
/*
 *  Das Wahre Schlagerfest. A simple game.
 *  Copyright (C) 2003  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitAboutBox.h"
#include <memory>
#include "UnitThreeDotsChasing.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

const int BACKGROUND = 0;
const int BRATWURST  = 1;
const int BIERTJE    = 2;
const int RICHEL     = 3;

const int maxx=9;
const int maxy=5;
int area[maxx][maxy];
int temparea[maxx][maxy];
int playerX,playerY;
int picture;
double morph=0.0;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{
  RichEdit1->Top = (maxy * 100) + 5;
  RichEdit1->Left = 25 + 25 + 100;
  RichEdit1->Refresh();
  ImageAnimation->Top = (maxy * 100) + 5;
  ImageAnimation->Left = RichEdit1->Left + RichEdit1->Width + 25;
  ImageMessage->Top = (maxy * 100) + 100 + 5;
  ImageMessage->Left = ImageAnimation->Left;
  ImageMessage->Refresh();
  this->ClientHeight = ImageMessage->Top + ImageMessage->Height;
  this->ClientWidth = (maxx * 100);
  ImagePressKeyDown->Left = (ClientWidth / 2) - (ImagePressKeyDown->Width / 2);
  ImagePressKeyDown->Top = ((maxy * 100) / 2) - (ImagePressKeyDown->Height / 2);;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Timer1->Enabled==false)
  {
    Initialize->Execute();
    Timer1->Enabled=true;
    ImagePressKeyDown->Visible = false;
    Refresh();
    DrawArea->Execute();
    DrawPlayer->Execute();
    return;
  }

  std::auto_ptr<TFormAboutBox> aboutBox;
  std::auto_ptr<TFormThreeDotsChasing> threeDotsChasing;


  switch (Key)
  {
    case 73 : //letter I
      if (ApplicationEvents1->Tag==0 || ApplicationEvents1->Tag==6)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case 76 : //Letter L
      if (ApplicationEvents1->Tag==1 || ApplicationEvents1->Tag==10)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      if (ApplicationEvents1->Tag==11)
        { //Easter egg found!
        ApplicationEvents1->Tag=0;
        aboutBox.reset(new TFormAboutBox(0));
        aboutBox->Hide();
        aboutBox->ShowModal();
        aboutBox.reset(0);
        threeDotsChasing.reset(new TFormThreeDotsChasing(0));
        threeDotsChasing->Hide();
        threeDotsChasing->ShowModal();
        threeDotsChasing.reset(0);
        DrawArea->Execute();
        DrawPlayer->Execute();
        }
      break;
    case 79 : //Letter O
      if (ApplicationEvents1->Tag==2)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case 86 : //Letter V
      if (ApplicationEvents1->Tag==3)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case 69 : //Letter E
      if (ApplicationEvents1->Tag==4 || ApplicationEvents1->Tag==9)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case 82 : //Letter R
      if (ApplicationEvents1->Tag==5)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case 67 : //Letter C
      if (ApplicationEvents1->Tag==7)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case 72 : //Letter H
      if (ApplicationEvents1->Tag==8)
        {ApplicationEvents1->Tag++;}
      else {ApplicationEvents1->Tag=0;}
      break;
    case VK_RIGHT :
      if (playerX<maxx-1 && area[playerX+1][playerY]==0 && picture!=RICHEL)
      {
        DeletePlayer->Execute();
        playerX++;
        DrawPlayer->Execute();
      }
      if (playerX<maxx-1 && picture==RICHEL)
      {
        area[playerX][playerY]=BACKGROUND;
        DeletePlayer->Execute();
        playerX++;
        DrawPlayer->Execute();
      }
      break;
    case VK_LEFT :
      if (playerX>0 && area[playerX-1][playerY]==0 && picture!=RICHEL)
      {
        DeletePlayer->Execute();
        playerX--;
        DrawPlayer->Execute();
      }
      if (playerX>0 && picture==RICHEL)
      {
        area[playerX][playerY]=BACKGROUND;
        DeletePlayer->Execute();
        playerX--;
        DrawPlayer->Execute();
      }
      break;
    case VK_DOWN :
      if ((playerY==maxy-1 || area[playerX][playerY+1]>0) && picture!=RICHEL)
      {//Block put on other block
        area[playerX][playerY]=picture;

        Find3Row->Execute();
        if (area[4][1]!=BACKGROUND)
            {picture=RICHEL;}
          else { picture = 1 + (std::rand() % 2) ;}
        playerX=4; playerY=0;
        DrawPlayer->Execute();
        break;
      }
      if (!(playerY==maxy-1 || area[playerX][playerY+1]>0) && picture!=RICHEL)
      {
        DeletePlayer->Execute();
        playerY++;
        DrawPlayer->Execute();
        break;
      }
      if (playerY<maxy-1 && picture==RICHEL)
      {
        area[playerX][playerY]=BACKGROUND;
        DeletePlayer->Execute();
        playerY++;
        DrawPlayer->Execute();
        break;
      }
      if (playerY==maxy-1 && picture==RICHEL)
      {
        area[playerX][playerY]=BACKGROUND;
        this->Canvas->Draw(playerX*100,playerY*100,ImageBackGround->Picture->Graphic);
        if (area[4][1]!=BACKGROUND)
            {picture=RICHEL;}
          else {picture=1+(std::rand()%2);}
        playerX=4; playerY=0;
        DrawPlayer->Execute();
        break;
      }
      break;
  //default: ShowMessage(Key); break;
  }//End of: switch(Key)
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Find3RowExecute(TObject *Sender)
{
int temparea[maxx][maxy];
bool FoundOne=false;
int y,x;

do
  {
  FoundOne=false;
  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      temparea[x][y]=0;
      }//next x
    }//next y

  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      if (x>1)
        {
        if ((area[x][y]*area[x-1][y]*area[x-2][y]==1)|| (area[x][y]*area[x-1][y]*area[x-2][y]==8))
          { temparea[x][y]=temparea[x-1][y]=temparea[x-2][y]=-1; FoundOne=true;}
        }
      if (y>1)
        {
        if ((area[x][y]*area[x][y-1]*area[x][y-2]==1) || (area[x][y]*area[x][y-1]*area[x][y-2]==8))
          {temparea[x][y]=temparea[x][y-1]=temparea[x][y-2]=-1; FoundOne=true;}
        }
      if (x<maxx-2)
        {
        if ((area[x][y]*area[x+1][y]*area[x+2][y]==1) || (area[x][y]*area[x+1][y]*area[x+2][y]==8))
          {temparea[x][y]=temparea[x+1][y]=temparea[x+2][y]=-1; FoundOne=true;}
        }
      if (y<maxy-2)
        {
        if ((area[x][y]*area[x][y+1]*area[x][y+2]==1) || (area[x][y]*area[x][y+1]*area[x][y+2]==8))
          {temparea[x][y]=temparea[x][y+1]=temparea[x][y+2]=-1; FoundOne=true;}
        }
      if (x>1 && y>1)
        {
        if ((area[x][y]*area[x-1][y-1]*area[x-2][y-2]==1) || (area[x][y]*area[x-1][y-1]*area[x-2][y-2]==8))
          {temparea[x][y]=temparea[x-1][y-1]=temparea[x-2][y-2]=-1; FoundOne=true;}
        }
      if (x>1 && y<maxy-2)
        {
        if ((area[x][y]*area[x-1][y+1]*area[x-2][y+2]==1)||(area[x][y]*area[x-1][y+1]*area[x-2][y+2]==8))
          {temparea[x][y]=temparea[x-1][y+1]=temparea[x-2][y+2]=-1; FoundOne=true;}
        }
      if (x<maxx-2 && y>1)
        {
        if ((area[x][y]*area[x+1][y-1]*area[x+2][y-2]==1)||(area[x][y]*area[x+1][y-1]*area[x+2][y-2]==8))
          {temparea[x][y]=temparea[x+1][y-1]=temparea[x+2][y-2]=-1; FoundOne=true;}
        }
      if (x<maxx-2 && y<maxy-2)
        {
        if ((area[x][y]*area[x+1][y+1]*area[x+2][y+2]==1)||(area[x][y]*area[x+1][y+1]*area[x+2][y+2]==8))
          {temparea[x][y]=temparea[x+1][y+1]=temparea[x+2][y+2]=-1; FoundOne=true;}
        }
      }//next x
    }//next y


  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      if (temparea[x][y]==-1)
        {
        temparea[x][y]=0;
        int i; for (i=y; i>0; i--)
          {
          area[x][i]=area[x][i-1];
          }//Next i
        area[x][0]=0;
        }
      }//next x
    }//next y
  }//End of do
  while (FoundOne==true);

DrawArea->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitializeExecute(TObject *Sender)
{
  int y,x;
  for (y=0; y<maxy; y++)
    {
    for (x=0; x<maxx; x++)
      {
      area[x][y]=BACKGROUND;
      temparea[x][y]=0;
      this->Canvas->Draw(x*100, y*100,ImageBackGround->Picture->Graphic);
      }//next x
    }//next y
  playerX=4;
  playerY=0;
  picture=1+(std::rand()%2);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DeletePlayerExecute(TObject *Sender)
{
  this->Canvas->Draw(playerX*100, playerY*100,ImageBackGround->Picture->Graphic);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DrawPlayerExecute(TObject *Sender)
{
switch (picture)
  {
  case BRATWURST : this->Canvas->Draw(playerX*100, playerY*100,ImageBratWurst->Picture->Graphic);
                   break;
  case BIERTJE   : this->Canvas->Draw(playerX*100, playerY*100,ImageBiertje->Picture->Graphic);
                   break;
  case RICHEL    : this->Canvas->Draw(playerX*100, playerY*100,ImageRichel->Picture->Graphic);
                   break;
  }//End of switch
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::DrawAreaExecute(TObject *Sender)
{
int y,x;
for (y=0; y<maxy; y++)
  {
  for (x=0; x<maxx; x++)
    {
    switch (area[x][y])
      {
      case BACKGROUND : this->Canvas->Draw(x*100, y*100,ImageBackGround->Picture->Graphic); break;
      case BRATWURST : this->Canvas->Draw(x*100, y*100,ImageBratWurst->Picture->Graphic); break;
      case BIERTJE : this->Canvas->Draw(x*100, y*100,ImageBiertje->Picture->Graphic); break;
      case RICHEL : this->Canvas->Draw(x*100, y*100,ImageRichel->Picture->Graphic); break;
      default : ShowMessage("Error!");
      }//End of: switch
    //StringGrid1->Cells[x][y]=area[x][y];
    }//next x
  }//next y
}
//---------------------------------------------------------------------------





void __fastcall TFormMain::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
  for (int y=0; y<ImageAnimation->Height; y++)
    {
    unsigned char * MyLineResult=(unsigned char *) ImageAnimation->Picture->Bitmap->ScanLine[y];
    unsigned char * MyLineBiertje=(unsigned char *) ImageBiertje->Picture->Bitmap->ScanLine[y];
    unsigned char * MyLineBratWurst=(unsigned char *) ImageBratWurst->Picture->Bitmap->ScanLine[y];
    for (int x=0; x<ImageAnimation->Width; x++)
      {
      MyLineResult[x*3]= (double)MyLineBiertje[x*3]*morph + (double)MyLineBratWurst[x*3]*(1.0-morph);
      MyLineResult[x*3+1]= (double)MyLineBiertje[x*3+1]*morph + (double)MyLineBratWurst[x*3+1]*(1.0-morph);
      MyLineResult[x*3+2]= (double)MyLineBiertje[x*3+2]*morph + (double)MyLineBratWurst[x*3+2]*(1.0-morph);
      }//next x
    }//next y

  if (ImageAnimation->Tag==0)
    {
    morph+=0.01;
    if (morph>1.0) {ImageAnimation->Tag=1; morph=1.0;}
    }
  else
    {
    morph-=0.01;
    if (morph<0.0) {ImageAnimation->Tag=0; morph=0.0;}
    }

  this->Canvas->Draw(ImageAnimation->Left,ImageAnimation->Top,ImageAnimation->Picture->Graphic);
  this->Canvas->Draw(25,ImageAnimation->Top,ImageAnimation->Picture->Graphic);
  Application->ProcessMessages();
  Done=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClick(TObject *Sender)
{
  DrawArea->Execute();
  DrawPlayer->Execute();

}
//---------------------------------------------------------------------------

