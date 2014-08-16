//---------------------------------------------------------------------------
/*
  Martian Cafe Tuinema Tycoon, bartender game
  Copyright (C) 2005  Joost van den Bogaart

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MCT1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int a[24][4];  //array met info over alle aliens
int b=0;       //array met welk veld hij laat zien:
                       // 0 = veld met bar
                       // 1 = veld met iets anders
int c[10][2];  //array met glazen
int aantalglazen=0; //aantal glazen op dienblad
int dwijlorkest=0; //welk dwijlorkestplaatje
int drinkssold=0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//Plaatjes inladen:
BackgroundImage->Picture->LoadFromFile("Background1.bmp");
ArrowImage->Picture->LoadFromFile("Arrow.bmp"); ArrowImage->Left=10; ArrowImage->Top=140;
L0Image->Picture->LoadFromFile("L0.bmp");
L1Image->Picture->LoadFromFile("L1.bmp");
L2Image->Picture->LoadFromFile("L2.bmp");
R0Image->Picture->LoadFromFile("R0.bmp");
R1Image->Picture->LoadFromFile("R1.bmp");
R2Image->Picture->LoadFromFile("R2.bmp");
ItemImage->Picture->LoadFromFile("Bar.bmp");
StaffImage->Picture->LoadFromFile("BarMan.bmp");
        ItemImage->Left=552; ItemImage->Top=312;
        StaffImage->Left=650; StaffImage->Top=310,
GlasImage->Picture->LoadFromFile("Glas.bmp");
DienbladImage->Picture->LoadFromFile("Dienblad.bmp");
OrkestImage1->Picture->LoadFromFile("Band1.bmp");
OrkestImage2->Picture->LoadFromFile("Band2.bmp");
WallImage->Picture->LoadFromFile("Wall.bmp");


//Belangrijke waarden inladen in array a:
//0=left, 1=top, 2=status voor veld 1 en 3=voor veld 2:
        //0 = plek leeg,
        //1 = bezet maar geen bier,
        //2 = drinkende.
//linker aliens
a[0][0]=257;  a[0][1]=297;   a[0][2]=0;   a[0][3]=0;
a[1][0]=217;  a[1][1]=337;   a[1][2]=0;   a[1][3]=0;
a[2][0]=421;  a[2][1]=298;   a[2][2]=0;   a[2][3]=0;
a[3][0]=381;  a[3][1]=338;   a[3][2]=0;   a[3][3]=0;
a[4][0]=127;  a[4][1]=425;   a[4][2]=0;   a[4][3]=0;
a[5][0]=87;   a[5][1]=465;   a[5][2]=0;   a[5][3]=0;
a[6][0]=278;  a[6][1]=428;   a[6][2]=0;   a[6][3]=0;
a[7][0]=237;  a[7][1]=469;   a[7][2]=0;   a[7][3]=0;
a[8][0]=424;  a[8][1]=430;   a[8][2]=0;   a[8][3]=0;
a[9][0]=384;  a[9][1]=470;   a[9][2]=0;   a[9][3]=0;
a[10][0]=592; a[10][1]=430;  a[10][2]=0;  a[10][3]=0;
a[11][0]=552; a[11][1]=470;  a[11][2]=0;  a[11][3]=0;
//rechter aliens
a[12][0]=315;  a[12][1]=289;   a[12][2]=0;  a[12][3]=0;
a[13][0]=270;  a[13][1]=334;   a[13][2]=0;  a[13][3]=0;
a[14][0]=477;  a[14][1]=293;   a[14][2]=0;  a[14][3]=0;
a[15][0]=436;  a[15][1]=333;   a[15][2]=0;  a[15][3]=0;
a[16][0]=188;  a[16][1]=414;   a[16][2]=0;  a[16][3]=0;
a[17][0]=145;   a[17][1]=457;   a[17][2]=0; a[17][3]=0;
a[18][0]=339;  a[18][1]=417;   a[18][2]=0;  a[18][3]=0;
a[19][0]=295;  a[19][1]=461;   a[19][2]=0;  a[19][3]=0;
a[20][0]=494;  a[20][1]=410;   a[20][2]=0;  a[20][3]=0;
a[21][0]=447;  a[21][1]=457;   a[21][2]=0;  a[21][3]=0;
a[22][0]=655; a[22][1]=417;  a[22][2]=0;    a[22][3]=0;
a[23][0]=615; a[23][1]=457;  a[23][2]=0;    a[23][3]=0;

//Glazen
//c[x][0]=left, top is altijd 360, [1]=of het glas er staat...
for (int a=0; a<10; a++)
        {
        c[a][0]=768-a*16;
        c[a][1]=0;
        }

//AlienGrid->Cells[0][0]=257; AlienGrid->Cells[0][1]=297;
//AlienGrid->Cells[0][0]=257; AlienGrid->Cells[0][1]=257;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::BewegingstimerTimer(TObject *Sender)
{

//Neerzetten met double buffering:
   //achtergrond
   ImageCanvas->Picture=BackgroundImage->Picture;

   //musica
   Beep(random(500),500);

   //staff laten bewegen als barman
   if (b==0)
        {
           StaffImage->Left=StaffImage->Left+random(50)-25;
                if (StaffImage->Left<600) StaffImage->Left=600;
                if (StaffImage->Left>700) StaffImage->Left=700;
                ImageCanvas->Canvas->Draw(StaffImage->Left,StaffImage->Top,StaffImage->Picture->Graphic);
                ImageCanvas->Canvas->Draw(ItemImage->Left,ItemImage->Top,ItemImage->Picture->Graphic);
        }
   else   //het dwijlorkest
        {
           switch (dwijlorkest)
                {
                case 0:
                  ImageCanvas->Canvas->Draw(524,100,OrkestImage1->Picture->Graphic);
                  dwijlorkest=1;
                  break;
                case 1:
                  ImageCanvas->Canvas->Draw(525,100,OrkestImage2->Picture->Graphic);
                  dwijlorkest=0;
                  break;
                }
        }

   //dienblad:
   ImageCanvas->Canvas->Draw(10,140,ArrowImage->Picture->Graphic);
   ImageCanvas->Canvas->Draw(8,80,DienbladImage->Picture->Graphic);
   for (int t=0; t<aantalglazen+1; t++)
        {
         switch (t)
                {
                 case 0:
                   break;
                 case 1:
                   ImageCanvas->Canvas->Draw(48,80,GlasImage->Picture->Graphic);
                   break;
                 case 2:
                   ImageCanvas->Canvas->Draw(63,82,GlasImage->Picture->Graphic);
                   break;
                 case 3:
                   ImageCanvas->Canvas->Draw(28,84,GlasImage->Picture->Graphic);
                   break;
                 case 4:
                   ImageCanvas->Canvas->Draw(14,94,GlasImage->Picture->Graphic);
                   break;
                 case 5:
                   ImageCanvas->Canvas->Draw(30,94,GlasImage->Picture->Graphic);
                   break;
                 case 6:
                   ImageCanvas->Canvas->Draw(47,89,GlasImage->Picture->Graphic);
                   break;
                 case 7:
                   ImageCanvas->Canvas->Draw(61,90,GlasImage->Picture->Graphic);
                   break;
                 case 8:
                   ImageCanvas->Canvas->Draw(56,96,GlasImage->Picture->Graphic);
                   break;
                 case 9:
                   ImageCanvas->Canvas->Draw(88,88,GlasImage->Picture->Graphic);
                   break;
                 case 10:
                   ImageCanvas->Canvas->Draw(90,95,GlasImage->Picture->Graphic);
                   break;
                 case 11:
                   ImageCanvas->Canvas->Draw(74,95,GlasImage->Picture->Graphic);
                   break;
                }
        }


   //de glazen vullen:
   if(random(3)==1) c[random(10)][1]=1;     //kans 1op30;

   //de glazen tekenen als de bar er is:
   if (b==0)
        {
           for (int we=0; we<10; we++)
                {
                switch (c[we][1])
                        {
                        case 0:
                           break;
                        case 1:
                           ImageCanvas->Canvas->Draw(c[we][0],360,GlasImage->Picture->Graphic);
                           break;
                        }
                }
        }//end glazenifstatement

   //Linker Aliens
   for (int we=0; we<12; we++)  //waar tekent hij ze?
       {
       switch (a[we][2+b])        //wat doen ze? +b=voor veld 2
          {
          case 0: //leeg
            break;
          case 1: //geen glas -snik-
            ImageCanvas->Canvas->Draw(a[we][0],a[we][1],L0Image->Picture->Graphic);
            break;
          case 2: //wel glas, al dan niet drinken
            switch (random(2))
                {
                case 0:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],L2Image->Picture->Graphic);
                break;
                case 1:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],L1Image->Picture->Graphic);
                break;
                }
            break;
          }
       }
   //Rechter Aliens
   for (int we=12; we<24; we++)  //waar tekent hij ze?
       {
       switch (a[we][2+b])        //wat doen ze?   //b voor veld 2
          {
          case 0: //leeg
            break;
          case 1: //geen glas -snik-
            ImageCanvas->Canvas->Draw(a[we][0],a[we][1],R0Image->Picture->Graphic);
            break;
          case 2: //wel glas, al dan niet drinken
            switch (random(2))
                {
                case 0:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],R2Image->Picture->Graphic);
                break;
                case 1:
                ImageCanvas->Canvas->Draw(a[we][0],a[we][1],R1Image->Picture->Graphic);
                break;
                }
            break;
          }
       }


//de muur:
ImageCanvas->Canvas->Draw(673,124,WallImage->Picture->Graphic);

//klaar
Form1->Canvas->Draw(0,0,ImageCanvas->Picture->Graphic);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ArrowImageClick(TObject *Sender)
{
//Ander veld inladen:
if (b==0) //nu veld2 met iets anders tonen
        {
        b = 1;
        BackgroundImage->Picture->LoadFromFile("Background2.bmp");
        }
else    // veld met bar tonen
        {
        b = 0;
        BackgroundImage->Picture->LoadFromFile("Background1.bmp");
        ItemImage->Picture->LoadFromFile("Bar.bmp");
        ItemImage->Left=552; ItemImage->Top=312;
        StaffImage->Left=650; StaffImage->Top=310,
        StaffImage->Picture->LoadFromFile("BarMan.bmp");
        }

//randomizeren aliens:
//lege plekken moeten misschien gevuld, aliens met leeg glas moeten misschien weg,
//drinkende aliens moeten misschien weer droog.
for (int we=0; we<24; we++)
      {
      //vullen lege plekken:
      if (a[we][2+b]==0)  //veld met alieninfo
          {
          a[we][2+b]=random(2);  //wordt misschien 1, dat is alien met leeg glas
          }
      //weghalen aliens met leeg glas na vullen lege plekken om te voorkomen dat de tent te snel volloopt!
      if (a[we][2+b]==1)
          {
          a[we][2+b]=random(2);  //wordt misschien 0, dat is leeg
          }
      // en de volle glazen gaan ooit leeg
      if (a[we][2+b]==2)
          {
          if (random(2)==1)
          a[we][2+b]=random(2)+1;  //wordt misschien 1, dat is leeg, kans 1 op 4
          }
      }



}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
//Aliens bier geven:
//Bepalen welke alien het is op basis van de volgende gegevens:
        //a[we][0] (left) +7-27 voor L en +21-44 voor R
        //a[we][1] (top) +18-53 voor L en +20-61 voor R
for (int we=0; we<12; we++)   //de linker aliens...
        {
        if (X>a[we][0]+7&&X<a[we][0]+27)
        if (Y>a[we][1]+18&&Y<a[we][1]+53)
        if (aantalglazen>0)
        if (a[we][2+b]==1)
                {
                a[we][2+b]=2;
                aantalglazen=aantalglazen-1;
                drinkssold++;
                DrinkLabel->Caption=drinkssold;
                }
        }
for (int we=12; we<24; we++)   //de rechter aliens...
        {
        if (X>a[we][0]+21&&X<a[we][0]+44)
        if (Y>a[we][1]+20&&Y<a[we][1]+61)
        if (aantalglazen>0)
        if (a[we][2+b]==1)
                {
                a[we][2+b]=2;
                aantalglazen=aantalglazen-1;
                drinkssold++;
                DrinkLabel->Caption=drinkssold;
                }
        }


//glazen pakken
if (b==0)
        {
        for (int we=0; we<10; we++)   //de glazen.
            {
            if (X>c[we][0]&&X<c[we][0]+15)
            if (Y>360&&Y<380)
            if (c[we][1]==1&&aantalglazen<11)  //niet meer dan 11 glazen op dienblad
                {
                aantalglazen++;   //glas erbij zetten
                c[we][1]=0;       //van de bar af;
                }
            }
        }

   //de glazen tekenen als de bar er is:
   if (b==0)
        {
           for (int we=0; we<10; we++)
                {
                switch (c[we][1])
                        {
                        case 0:
                           break;
                        case 1:
                           ImageCanvas->Canvas->Draw(c[we][0],360,GlasImage->Picture->Graphic);
                           break;
                        }
                }
        }//end glazenifstatement

}
//---------------------------------------------------------------------------


