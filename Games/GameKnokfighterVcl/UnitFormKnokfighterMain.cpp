//---------------------------------------------------------------------------
/*
    KnokFighter, a simple fighting game
    Copyright (C) 2005  Richel Bilderbeek and Joost van den Bogaart

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
#include <vcl.h>
#pragma hdrstop
#include <mmsystem.h>
#include "UnitFormKnokfighterMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;


const int JOOSTSTAATLINKS            =  1;
const int JOOSTSTAATRECHTS           =  2;
const int JOOSTLOOPTLINKS1           =  3;
const int JOOSTLOOPTLINKS2           =  4;
const int JOOSTLOOPTRECHTS1          =  5;
const int JOOSTLOOPTRECHTS2          =  6;
const int JOOSTSLAATLINKS1           =  7;
const int JOOSTSLAATLINKS2           =  8;
const int JOOSTSCHOPTLANGZAAMLINKS   =  9;
const int JOOSTSCHOPTSNELLINKS       = 10;
const int JOOSTSLAATRECHTS1          = 11;
const int JOOSTSLAATRECHTS2          = 12;
const int JOOSTSCHOPTLANGZAAMRECHTS  = 13;
const int JOOSTSCHOPTSNELRECHTS      = 14;
const int JOOSTSLAATLINKSLAAG        = 15;
const int JOOSTSLAATRECHTSLAAG       = 16;

const int RICHELSTAATLINKS           =   1;
const int RICHELSTAATRECHTS          =   2;
const int RICHELLOOPTLINKS1          =   3;
const int RICHELLOOPTLINKS2          =   4;
const int RICHELLOOPTRECHTS1         =   5;
const int RICHELLOOPTRECHTS2         =   6;
//HP
const int RICHELSLAATHOOGLINKS1      =   7;
const int RICHELSLAATHOOGLINKS2      =   8;
const int RICHELSLAATHOOGRECHTS1     =   9;
const int RICHELSLAATHOOGRECHTS2     =  10;
//LP
const int RICHELSLAATLAAGLINKS       =  11;
const int RICHELSLAATLAAGRECHTS      =  12;
//HK
const int RICHELSCHOPTHOOGLINKS      =  13;
const int RICHELSCHOPTHOOGRECHTS     =  14;
//LK
const int RICHELSCHOPTLAAGLINKS      =  15;
const int RICHELSCHOPTLAAGRECHTS     =  16;

const int VK_JLP = 65; //A
const int VK_JHP = 81; //Q
const int VK_JLK = 83; //S
const int VK_JHK = 87; //W

enum PROGSTATE {UnInitialized, Initialized, PreRunning, Running};

PROGSTATE ProgramState=UnInitialized;

int JoostHealth = 1000;  //joosts health
int RichelHealth = 1000; //richels health
int RichelBonus = 100; //de damagebonus van een kick, hoger is slechter...
int JoostBonus = 100;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ApplicationEvents1Idle(TObject *Sender,
      bool &Done)
{
  switch (ProgramState)
  {
    case Running:
      //TEKEN HET SCHERM
      //Zet het plaatje van de geheime canvas gelijk aan de achtergrond
      ImageCanvas->Picture=ImageBackGround->Picture;
      //Teken Richel op de achtergrond
      ImageCanvas->Canvas->Draw(Richel->Left,Richel->Top,Richel->Picture->Graphic);
      //Teken Joost op de achtergrond
      ImageCanvas->Canvas->Draw(Joost->Left,Joost->Top,Joost->Picture->Graphic);
      //Teken het schadewolkje!
      ImageCanvas->Canvas->Draw(Wolk->Left,Wolk->Top,Wolk->Picture->Graphic);
      //Teken de geheime canvas op de Form
      FormMain->Canvas->Draw(0,0,ImageCanvas->Picture->Graphic);
      break;
    case PreRunning :
      //Zet het plaatje van de geheime canvas gelijk aan de achtergrond
      ImageCanvas->Picture=ImageBackGround->Picture;
      //Zet Joost op de juiste plek
      Joost->Left=ImageCanvas->Width - Joost->Width-20;
      Joost->Top=ImageCanvas->Height-Joost->Height-20;
      //Zet Richel op de juiste plek
      Richel->Left=20;
      Richel->Top=ImageCanvas->Height-Richel->Height-20;
      //Teken Joost op de achtergrond
      ImageCanvas->Canvas->Draw(Joost->Left,Joost->Top,Joost->Picture->Graphic);
      //Teken Richel op de achtergrond
      ImageCanvas->Canvas->Draw(Richel->Left,Richel->Top,Richel->Picture->Graphic);
      //Teken de geheime canvas op de Form
      FormMain->Canvas->Draw(0,0,ImageCanvas->Picture->Graphic);
      Joost->Tag=JOOSTSTAATLINKS;
      Richel->Tag=RICHELSTAATRECHTS;
      ProgramState=Running;
      break;
    case Initialized :
      break;
    case UnInitialized :
      //Zet het plaatje van de geheime canvas gelijk aan de achtergrond
      ImageCanvas->Picture=Startscherm->Picture;
      //Teken de achtergrond op FormMain
      FormMain->Canvas->Draw(0,0,ImageCanvas->Picture->Graphic);
      ProgramState=Initialized;
      break;
  }//End of: switch(ProgramState)
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch (ProgramState)
  {
    case Running:
      //Het programma loopt. Welke toets wordt ingedrukt?
      switch (Key)
      {
        case VK_LEFT :
          //Ha, links wordt ingedrukt. Hoe staat het met Joost nu?
          switch (Joost->Tag)
          {
            case JOOSTSTAATLINKS :
              //Joost staat en loopt nu naar links
              Joost->Picture->LoadFromFile("JoostLooptLinks1.bmp");
              JoostShadow->Picture->LoadFromFile("JoostLooptLinks1Shadow.bmp");
              Joost->Left -= 10;
              Joost->Tag=JOOSTLOOPTLINKS1;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=250;
              break; //Break JOOSTSTAATLINKS
            case JOOSTLOOPTLINKS1 :
              break; //Break JOOSTLOOPTLINKS1
            case JOOSTLOOPTLINKS2 :
              break; //Break JOOSTSLOOPTLINKS2
            case JOOSTSTAATRECHTS :
              //Joost kijkt naar rechts en gaat nu naar links kijken
              Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
              JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
              Joost->Tag=JOOSTSTAATLINKS;
              break; //Break case JOOSTSTAATRECHTS
            }//End of: switch (Joost->Tag)
          break; //Break case VK_LEFT
        case VK_RIGHT :
          //Ha, rechts wordt ingedrukt. Hoe staat het met Joost nu?
          switch (Joost->Tag)
            {
            case JOOSTSTAATLINKS :
              //Joost kijkt naar links en gaat nu naar rechts kijken
              Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
              JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
              Joost->Tag=JOOSTSTAATRECHTS;
              break; //Break case JOOSTSTAATLINKS
            case JOOSTSTAATRECHTS :
              //Joost staat en loopt nu naar rechts
              Joost->Picture->LoadFromFile("JoostLooptRechts1.bmp");
              JoostShadow->Picture->LoadFromFile("JoostLooptRechts1Shadow.bmp");
              Joost->Left += 10;
              Joost->Tag=JOOSTLOOPTRECHTS1;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=250;
              break; //Break JOOSTSTAATRECHTS
            case JOOSTLOOPTRECHTS1 :
              break; //Break JOOSTLOOPTRECHTS1
            case JOOSTLOOPTRECHTS2 :
              break; //Break JOOSTSLOOPTRECHTS2
            }//End of: switch (Joost->Tag)
          break; //Break case VK_LEFT

        case VK_UP :
          break; //Break case VK_LEFT
        case VK_DOWN :
          break; //Break case VK_LEFT
        case VK_JLP :
          //de Low Punch knop van Joost wordt ingedrukt. Hoe staat Joost erbij?

          switch (Joost->Tag)
          {
            case JOOSTSTAATLINKS:
              JoostBonus=55;
              PlaySound("Joostslaatlaag.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Picture->LoadFromFile("JoostSlaatLinksLaag.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSlaatLinksLaagShadow.bmp");
              Joost->Tag=JOOSTSLAATLINKSLAAG;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=500;
              break; //break case JOOSTSTAATLINKS
            case JOOSTSTAATRECHTS:
              JoostBonus=55;
              PlaySound("Joostslaatlaag.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Picture->LoadFromFile("JoostSlaatRechtsLaag.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSlaatRechtsLaagShadow.bmp");
              Joost->Tag=JOOSTSLAATRECHTSLAAG;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=500;
              break; //break case JOOSTSTAATRECHTS
          }//End of switch(Joost->Tag)

          break; //break case VK_JLP
        case VK_JHP :

          //de High Punch knop van Joost wordt ingedrukt. Hoe staat Joost erbij?
          switch (Joost->Tag)
            {
            case JOOSTSTAATLINKS:
              JoostBonus=45;
              PlaySound("Joostslaathoog.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Picture->LoadFromFile("JoostSlaatLinks1.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSlaatLinks1Shadow.bmp");
              Joost->Tag=JOOSTSLAATLINKS1;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=500;
              break; //break case JOOSTSTAATLINKS
            case JOOSTSTAATRECHTS:
              JoostBonus=45;
              PlaySound("Joostslaathoog.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Picture->LoadFromFile("JoostSlaatRechts1.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSlaatRechts1Shadow.bmp");
              Joost->Tag=JOOSTSLAATRECHTS1;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=500;
              break; //break case JOOSTSTAATRECHTS
          }//End of switch(Joost->Tag)
          break; //break case VK_JHP
        case VK_JLK :
          //de Low Kick knop van Joost wordt ingedrukt. Hoe staat Joost erbij?
          switch (Joost->Tag)
          {

            case JOOSTSTAATLINKS:
              JoostBonus=40;
              PlaySound("Joostschoplaag.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Picture->LoadFromFile("JoostSchoptSnelLinks.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSchoptSnelLinksShadow.bmp");
              Joost->Tag=JOOSTSCHOPTSNELLINKS;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=500;
              Joost->Top+=30;

              break; //break case JOOSTSTAATLINKS
            case JOOSTSTAATRECHTS:
              JoostBonus=40;
              PlaySound("Joostschoplaag.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Picture->LoadFromFile("JoostSchoptSnelRechts.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSchoptSnelRechtsShadow.bmp");
              Joost->Tag=JOOSTSCHOPTSNELRECHTS;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=500;
              Joost->Top+=30;
              break; //break case JOOSTSTAATRECHTS
          }//End of switch(Joost->Tag)
          break; //break case VK_JHK

        case VK_JHK :
          //de High Kick knop van Joost wordt ingedrukt. Hoe staat Joost erbij?
          switch (Joost->Tag)
          {
            case JOOSTSTAATLINKS:
              JoostBonus=30;
              PlaySound("Joostschophoog.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Top-=80;
              Joost->Picture->LoadFromFile("JoostSchoptLangzaamLinks.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSchoptLangzaamLinksShadow.bmp");
              Joost->Tag=JOOSTSCHOPTLANGZAAMLINKS;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=1500;
              break; //break case JOOSTSTAATLINKS
            case JOOSTSTAATRECHTS:
              JoostBonus=30;
              PlaySound("Joostschophoog.wav",NULL, SND_ASYNC | SND_FILENAME);
              Joost->Top-=80;
              Joost->Picture->LoadFromFile("JoostSchoptLangzaamRechts.bmp");
              JoostShadow->Picture->LoadFromFile("JoostSchoptLangzaamRechtsShadow.bmp");
              Joost->Tag=JOOSTSCHOPTLANGZAAMRECHTS;
              TimerJoost->Enabled=true;
              TimerJoost->Interval=1500;
              break; //break case JOOSTSTAATRECHTS
          }//End of switch(Joost->Tag)
          break; //break case VK_JLK

        default:
          //ShowMessage(Key);
          break; //Break case default Key
        }//End of: switch (Key)
      break;
    case Initialized :
      ProgramState=PreRunning;
      break;
  }//End of: switch (ProgramState)
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerJoostTimer(TObject *Sender)
{
  //Doet Joost Richel schade, zo ja hoeveel?
  int RichelDamage=0;   //integer met de schade van richel
  RichelShadow->Left=Richel->Left; //shadow achter figuur plaatsen
  RichelShadow->Top=Richel->Top;
  JoostShadow->Left=Joost->Left;
  JoostShadow->Top=Joost->Top;
  //Joosts Shadows rode gedeelte doet schade:
  for(int A=0;A<JoostShadow->Width;A++)
  {
    for(int B=0;B<JoostShadow->Height;B++)
    {
      if(JoostShadow->Canvas->Pixels[A][B]==clRed)
      {
        const int C = A+JoostShadow->Left-RichelShadow->Left;
        const int D = B+JoostShadow->Top-RichelShadow->Top;
        if(RichelShadow->Canvas->Pixels[C][D]==clLime)
        RichelDamage++;  //schade
        //wolkje
        if(WolkTimer->Enabled==false)
        {
          WolkTimer->Enabled=true;
          Wolk->Left=A+JoostShadow->Left+10;
          Wolk->Top=B+JoostShadow->Top+10;
        }
      }
    }
  }

  RichelDamage=RichelDamage/JoostBonus;
  RichelHealth=RichelHealth-RichelDamage;
  RichelHealthBar->Position=RichelHealth;

  switch (Joost->Tag)
  {
    case JOOSTLOOPTLINKS1:
      Joost->Picture->LoadFromFile("JoostLooptLinks2.bmp");
      JoostShadow->Picture->LoadFromFile("JoostLooptLinks2Shadow.bmp");
      Joost->Tag=JOOSTLOOPTLINKS2;
      Joost->Left -= 15;
      //TimerJoost->Enabled=true;
      //TimerJoost->Interval=500;
      break; //Break case JOOSTLOOPTLINKS1
    case JOOSTLOOPTLINKS2:
      Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
      Joost->Left -= 15;
      Joost->Tag=JOOSTSTAATLINKS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTLOOPTLINKS2
    case JOOSTLOOPTRECHTS1:
      Joost->Picture->LoadFromFile("JoostLooptRechts2.bmp");
      JoostShadow->Picture->LoadFromFile("JoostLooptRechts2Shadow.bmp");
      Joost->Tag=JOOSTLOOPTRECHTS2;
      Joost->Left += 15;
      //TimerJoost->Enabled=true;
      //TimerJoost->Interval=500;
      break; //Break case JOOSTLOOPTRECHTS1
    case JOOSTLOOPTRECHTS2:
      Joost->Picture->LoadFromFile("JoostStaatRechts.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatRechtsShadow.bmp");
      Joost->Tag=JOOSTSTAATRECHTS;
      Joost->Left += 15;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTLOOPTRECHTS2
    case JOOSTSLAATLINKS1:
      Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
      Joost->Tag=JOOSTSTAATLINKS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSLAATLINKS
    case JOOSTSLAATRECHTS1:
      Joost->Picture->LoadFromFile("JoostStaatRechts.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatRechtsShadow.bmp");
      Joost->Tag=JOOSTSTAATRECHTS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSLAATRECHTS

    case JOOSTSLAATLINKSLAAG:
      Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
      Joost->Tag=JOOSTSTAATLINKS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSLAATLINKS
    case JOOSTSLAATRECHTSLAAG:
      Joost->Picture->LoadFromFile("JoostStaatRechts.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatRechtsShadow.bmp");
      Joost->Tag=JOOSTSTAATRECHTS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSLAATRECHTS

    case JOOSTSCHOPTLANGZAAMLINKS:
      Joost->Top+=80;
      Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
      Joost->Tag=JOOSTSTAATLINKS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSCHOPTLINKS
    case JOOSTSCHOPTLANGZAAMRECHTS:
      Joost->Top+=80;
      Joost->Picture->LoadFromFile("JoostStaatRechts.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatRechtsShadow.bmp");
      Joost->Tag=JOOSTSTAATRECHTS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSCHOPTRECHTS

    case JOOSTSCHOPTSNELLINKS:
      Joost->Top-=30;
      Joost->Picture->LoadFromFile("JoostStaatLinks.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatLinksShadow.bmp");
      Joost->Tag=JOOSTSTAATLINKS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSCHOPTLINKS
    case JOOSTSCHOPTSNELRECHTS:
      Joost->Top-=30;
      Joost->Picture->LoadFromFile("JoostStaatRechts.bmp");
      JoostShadow->Picture->LoadFromFile("JoostStaatRechtsShadow.bmp");
      Joost->Tag=JOOSTSTAATRECHTS;
      TimerJoost->Enabled=false;
      break; //Break case JOOSTSCHOPTRECHTS
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TimerRichelTimer(TObject *Sender)
{
  //Doet Richel Joost schade, zo ja hoeveel?
  int JoostDamage=0;   //integer met de schade van joost
  RichelShadow->Left=Richel->Left; //shadow achter figuur plaatsen
  RichelShadow->Top=Richel->Top;
  JoostShadow->Left=Joost->Left;
  JoostShadow->Top=Joost->Top;
  //Richels Shadows rode gedeelte doet schade:
  for(int A=0;A<RichelShadow->Width;A++)
  {
    for(int B=0;B<RichelShadow->Height;B++)
    {
      if(RichelShadow->Canvas->Pixels[A][B]==clRed)
      {
        //raken ze elkander?
        const int C = A+RichelShadow->Left-JoostShadow->Left;
        const int D = B+RichelShadow->Top-JoostShadow->Top;
        if(JoostShadow->Canvas->Pixels[C][D]==clLime)
        JoostDamage++;
        if(WolkTimer->Enabled==false)
        {
          WolkTimer->Enabled=true;
          Wolk->Left=A+RichelShadow->Left+10;
          Wolk->Top=B+RichelShadow->Top+10;
        }
      }
    }
  }

  JoostDamage=JoostDamage/RichelBonus;
  JoostHealth=JoostHealth-JoostDamage;
  JoostHealthBar->Position=JoostHealth;

  switch (Richel->Tag)
  {
    case RICHELLOOPTLINKS1:
      Richel->Picture->LoadFromFile("RichelLooptLinks2.bmp");
      RichelShadow->Picture->LoadFromFile("RichelLooptLinks2Shadow.bmp");
      Richel->Tag=RICHELLOOPTLINKS2;
      Richel->Left -= 20;
      //TimerRichel->Enabled=true;
      //TimerRichel->Interval=500;
      break; //Break case RICHELLOOPTLINKS1
    case RICHELLOOPTLINKS2:
      Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
      Richel->Left -= 10;
      Richel->Tag=RICHELSTAATLINKS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELLOOPTLINKS2
    case RICHELLOOPTRECHTS1:
      Richel->Picture->LoadFromFile("RichelLooptRechts2.bmp");
      RichelShadow->Picture->LoadFromFile("RichelLooptRechts2Shadow.bmp");
      Richel->Tag=RICHELLOOPTRECHTS2;
      Richel->Left += 20;
      //TimerRichel->Enabled=true;
      //TimerRichel->Interval=500;
      break; //Break case RICHELLOOPTRECHTS1
    case RICHELLOOPTRECHTS2:
      Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
      Richel->Left += 10;
      Richel->Tag=RICHELSTAATRECHTS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELLOOPTRECHTS2
    case RICHELSLAATHOOGLINKS1:
      Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
      Richel->Tag=RICHELSTAATLINKS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSLAATLINKS
    case RICHELSLAATHOOGRECHTS1:
      Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
      Richel->Tag=RICHELSTAATRECHTS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSLAATRECHTS
    case RICHELSLAATLAAGLINKS:
      Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
      Richel->Tag=RICHELSTAATLINKS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSLAATLINKS
    case RICHELSLAATLAAGRECHTS:
      Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
      Richel->Tag=RICHELSTAATRECHTS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSLAATRECHTS
    case RICHELSCHOPTLAAGLINKS:
      Richel->Top+=80;
      Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
      Richel->Tag=RICHELSTAATLINKS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSCHOPTLINKS
    case RICHELSCHOPTLAAGRECHTS:
      Richel->Top+=80;
      Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
      Richel->Tag=RICHELSTAATRECHTS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSCHOPTRECHTS
    case RICHELSCHOPTHOOGLINKS:
      Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
      Richel->Tag=RICHELSTAATLINKS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSCHOPTLINKS
    case RICHELSCHOPTHOOGRECHTS:
      Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
      RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
      Richel->Tag=RICHELSTAATRECHTS;
      TimerRichel->Enabled=false;
      break; //Break case RICHELSCHOPTRECHTS
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::RichelAITimerTimer(TObject *Sender)
{
  //RICHEL'S AI
  if (Richel->Left-Joost->Left>100)
  {
    //Ha, Richel moet naar links. Hoe staat het met Richel nu?
    switch (Richel->Tag)
    {
      case RICHELSTAATLINKS :
        //Richel staat en loopt nu naar links
        Richel->Picture->LoadFromFile("RichelLooptLinks1.bmp");
        RichelShadow->Picture->LoadFromFile("RichelLooptLinks1Shadow.bmp");
        Richel->Left -= 10;
        Richel->Tag=RICHELLOOPTLINKS1;
        TimerRichel->Enabled=true;
        TimerRichel->Interval=250;
        break; //Break RICHELSTAATLINKS
      case RICHELLOOPTLINKS1 :
        break; //Break RICHELLOOPTLINKS1
      case RICHELLOOPTLINKS2 :
        break; //Break RICHELSLOOPTLINKS2
      case RICHELSTAATRECHTS :
        //Richel kijkt naar rechts en gaat nu naar links kijken
        Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
        RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
        Richel->Tag=RICHELSTAATLINKS;
        break; //Break case RICHELSTAATRECHTS
    }//End of: switch (Richel->Tag)
  }  //einde naar links
  else if (Joost->Left-Richel->Left>100) //naar rechts?
  { //naar rechts. Hoe staat het met Richel nu?
    switch (Richel->Tag)
    {
      case RICHELSTAATLINKS :
        //Richel kijkt naar links en gaat nu naar rechts kijken
        Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
        RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
        Richel->Tag=RICHELSTAATRECHTS;
        break; //Break case RICHELSTAATLINKS
      case RICHELSTAATRECHTS :
        //Richel staat en loopt nu naar rechts
        Richel->Picture->LoadFromFile("RichelLooptRechts1.bmp");
        RichelShadow->Picture->LoadFromFile("RichelLooptRechts1Shadow.bmp");
        Richel->Left += 10;
        Richel->Tag=RICHELLOOPTRECHTS1;
        TimerRichel->Enabled=true;
        TimerRichel->Interval=250;
        break; //Break RICHELSTAATRECHTS
      case RICHELLOOPTRECHTS1 :
        break; //Break RICHELLOOPTRECHTS1
      case RICHELLOOPTRECHTS2 :
        break; //Break RICHELSLOOPTRECHTS2
    }//End of: switch (Richel->Tag)
  }
  else if(Richel->Tag==RICHELSTAATRECHTS&&Richel->Left-Joost->Left>0)
  {
    //als richel de verkeerde kant opkijkt...
    //Richel kijkt naar rechts en gaat nu naar links kijken
    Richel->Picture->LoadFromFile("RichelStaatLinks.bmp");
    RichelShadow->Picture->LoadFromFile("RichelStaatLinksShadow.bmp");
    Richel->Tag=RICHELSTAATLINKS;
  }
  else if(Richel->Tag==RICHELSTAATLINKS&&Richel->Left-Joost->Left<0)
  {
    //als richel de verkeerde kant opkijkt...
    //Richel kijkt naar links en gaat nu naar rechts kijken
    Richel->Picture->LoadFromFile("RichelStaatRechts.bmp");
    RichelShadow->Picture->LoadFromFile("RichelStaatRechtsShadow.bmp");
    Richel->Tag=RICHELSTAATRECHTS;
  }
  else //lopen is niet noodzakelijk, richel moet een random vechtbeweging doen:
  {
    switch(random(6))
    {
      case 1: //een Low Punch. Hoe staat Richel erbij?
        switch (Richel->Tag)
        {
          case RICHELSTAATLINKS:
            RichelBonus=30;
            PlaySound("Richelslaatlaag.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSlaatLaagLinks.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSlaatLaagLinksShadow.bmp");
            Richel->Tag=RICHELSLAATLAAGLINKS;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
            break; //break case RICHELSTAATLINKS
          case RICHELSTAATRECHTS:
            RichelBonus=30;
            PlaySound("Richelslaatlaag.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSlaatLaagRechts.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSlaatLaagRechtsShadow.bmp");
            Richel->Tag=RICHELSLAATLAAGRECHTS;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
            break; //break case RICHELSTAATRECHTS
        }//End of switch(Richel->Tag)
        break; //break case VK_JLP
      case 2:
        //een High Punch. Hoe staat Richel erbij?
        switch (Richel->Tag)
        {
          case RICHELSTAATLINKS:
            RichelBonus=30;
            PlaySound("Richelslaathoog.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSlaatHoogLinks.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSlaatHoogLinksShadow.bmp");
            Richel->Tag=RICHELSLAATHOOGLINKS1;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
          break; //break case RICHELSTAATLINKS
          case RICHELSTAATRECHTS:
            RichelBonus=30;
            PlaySound("Richelslaathoog.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSlaatHoogRechts.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSlaatHoogRechtsShadow.bmp");
            Richel->Tag=RICHELSLAATHOOGRECHTS1;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
          break; //break case RICHELSTAATRECHTS
        }//End of switch(Richel->Tag)
        break; //break case VK_JHP
      case 3:
        //een Low Kick knop. Hoe staat Richel erbij?
        switch (Richel->Tag)
        {
          case RICHELSTAATLINKS:
            RichelBonus=40;
            PlaySound("Richelschoptlaag.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSchoptLaagLinks.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSchoptLaagLinksShadow.bmp");
            Richel->Tag=RICHELSCHOPTLAAGLINKS;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
            Richel->Top-=80;

          break; //break case RICHELSTAATLINKS
          case RICHELSTAATRECHTS:
            RichelBonus=40;
            PlaySound("Richelschoptlaag.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSchoptLaagRechts.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSchoptLaagRechtsShadow.bmp");
            Richel->Tag=RICHELSCHOPTLAAGRECHTS;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
            Richel->Top-=80;
          break; //break case RICHELSTAATRECHTS
        }//End of switch(Richel->Tag)
        break; //break case VK_JHK
      case 4:
        //een High Kick. Hoe staat Richel erbij?
        switch (Richel->Tag)
        {
          case RICHELSTAATLINKS:
            RichelBonus=40;
            PlaySound("Richelschopthoog.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSchoptHoogLinks.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSchoptHoogLinksShadow.bmp");
            Richel->Tag=RICHELSCHOPTHOOGLINKS;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
            break; //break case RICHELSTAATLINKS
          case RICHELSTAATRECHTS:
            RichelBonus=40;
            PlaySound("Richelschopthoog.wav",NULL, SND_ASYNC | SND_FILENAME);
            Richel->Picture->LoadFromFile("RichelSchoptHoogRechts.bmp");
            RichelShadow->Picture->LoadFromFile("RichelSchoptHoogRechtsShadow.bmp");
            Richel->Tag=RICHELSCHOPTHOOGRECHTS;
            TimerRichel->Enabled=true;
            TimerRichel->Interval=500;
            break; //break case RICHELSTAATRECHTS
        }//End of switch(Richel->Tag)
        break; //break case VK_JLK
    }
  }//end else
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::WolkTimerTimer(TObject *Sender)
{
  //tekst inladen
  switch (random(3))
  {
    case 0:
      Wolk->Picture->LoadFromFile("Wolk3.bmp");
      break;
    case 1:
      Wolk->Picture->LoadFromFile("Wolk2.bmp");
      break;
    case 2:
      Wolk->Picture->LoadFromFile("Wolk1.bmp");
      break;
  }

  //wolk verstoppen
  Wolk->Top=-500;
  WolkTimer->Enabled=false;

  //als het spel afgelopen is:
  if(RichelHealthBar->Position<1)
  {
    RichelAITimer->Enabled=false;
    ShowMessage("Richel is dead! Evil is defeated!");
    FormMain->Close();
  }
  else if(JoostHealthBar->Position<1)
  {
    RichelAITimer->Enabled=false;
    ShowMessage("Joost is defeated! All hope for mankind is lost!");
    FormMain->Close();
  }
}
//---------------------------------------------------------------------------

