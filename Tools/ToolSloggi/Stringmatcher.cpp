//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#pragma hdrstop

#include "Stringmatcher.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenButton1Click(TObject *Sender)
{
OpenDialog1->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenButton2Click(TObject *Sender)
{
OpenDialog2->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenDialog1CanClose(TObject *Sender,
      bool &CanClose)
{
OpenMemo1->Clear();
OpenMemo1->Lines->LoadFromFile(OpenDialog1->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenDialog2CanClose(TObject *Sender,
      bool &CanClose)
{
OpenMemo2->Clear();
OpenMemo2->Lines->LoadFromFile(OpenDialog2->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveButtonClick(TObject *Sender)
{
SaveDialog1->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SaveDialog1CanClose(TObject *Sender,
      bool &CanClose)
{
//Bij sluiten savedialog, opslaan met bestandsnaam:

AnsiString naambestand;
naambestand = ChangeFileExt(SaveDialog1->FileName,".csv");
SaveMemo->Lines->SaveToFile(naambestand);
ShowMessage("Bestand opgeslagen als "+naambestand);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MatchButtonClick(TObject *Sender)
{
//SaveMemo wissen
SaveMemo->Clear();

int Wat;
if (RadioButton1->Checked==true) {Wat = 1;}
if (RadioButton2->Checked==true) {Wat = 2;}
if (RadioButton3->Checked==true) {Wat = 3;}
if (RadioButton4->Checked==true) {Wat = 4;}
//if (RadioButton5->Checked==true) {Wat = 5;}
//if (RadioButton6->Checked==true) {Wat = 6;}

//Eerst uitvinden op welke positie de eerste puntkomma staat...
//En daarbij naar de tweede regel kijken

int Positie = OpenMemo1->Lines->Strings[1].AnsiPos(";");

if (DifferentBox->Checked==true)
        {
        Positie=ValueField->Text.ToIntDef(0);
        }

//Ingeval Wat = 3 of 4 moet hij gegevens uit het savememo weggooien. Deze moeten eerst geladen worden:
switch(Wat)
        {
        case 3:
        SaveMemo->Lines=OpenMemo2->Lines;
        break;
        case 4:
        SaveMemo->Lines=OpenMemo1->Lines;
        break;
        }



//Positie bevat nu de eerste "positie van ;
//In een dubbele FOR-loop gaat hij beide vergelijken:


int max1 = OpenMemo1->Lines->Count;
int max2 = OpenMemo2->Lines->Count;

AnsiString String1;
AnsiString String2;

for (int tel1 = 0; tel1<max1 ; tel1++)
        {
        String1 = OpenMemo1->Lines->Strings[tel1].SubString(1,Positie-1);
        for (int tel2 = 0; tel2<max2 ; tel2++)
                {
                        //De ruimte voor Positie worden de te vergelijken substrings
                        String2 = OpenMemo2->Lines->Strings[tel2].SubString(1,Positie-1);



                        //Dan de 6 mogelijkheden:
                        switch(Wat)
                                {
                                case 1:
                                //Eerste is gegevens rechterlijst wissen als niet in linkerlijst
                                if(String1==String2)
                                        {
                                        SaveMemo->Lines->Add(OpenMemo2->Lines->Strings[tel2]);
                                        }
                                break;
                                case 2:
                                //Tweede is gegevens linkerlijst wissen als niet in rechterlijst
                                if(String1==String2)
                                        {
                                        SaveMemo->Lines->Add(OpenMemo1->Lines->Strings[tel1]);
                                        }
                                break;
                                case 3:
                                case 4:
                                //Derde en vierde is gegevens wissen die ook in andere lijst staan
                                //daarvoor het hele bestand doorzoeken, omdat er immers regels gewist worden
                                if(String1==String2)
                                {
                                        for (int tel3 = 0; tel3<SaveMemo->Lines->Count; tel3++)
                                                {
                                                if (SaveMemo->Lines->Strings[tel3].SubString(1,Positie-1)==String2)
                                                        {
                                                        SaveMemo->Lines->Delete(tel3);
                                                        }
                                                }//end tel3-forloop
                                        }
                                break; //end case 3 en 4
                                }//end switch(wat)

                }//end forloop tel2
        }//end forloop tel1

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToSaveButton1Click(TObject *Sender)
{
//Zet de gegevens uit openmemo1 naar savememo
SaveMemo->Lines=OpenMemo1->Lines;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToSaveButton2Click(TObject *Sender)
{
//Zet de gegevens uit openmemo2 naar savememo
SaveMemo->Lines=OpenMemo2->Lines;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CombineButton1Click(TObject *Sender)
{
//Voegt gegevens uit andere lijst achter gegevens in deze lijst.
//Via dubbele For-loop:
int Positie = OpenMemo1->Lines->Strings[1].AnsiPos(";");

if (DifferentBox->Checked==true)
        {
        Positie=ValueField->Text.ToIntDef(0);
        }

int max1 = OpenMemo1->Lines->Count;
int max2 = OpenMemo2->Lines->Count;

AnsiString String1;
AnsiString String2;

SaveMemo->Clear();

//Dubbele forloop
for (int tel1 = 0; tel1<max1 ; tel1++)
        {
        //Default is regels toevoegen uit eigen memo
        String1 = OpenMemo1->Lines->Strings[tel1].SubString(1,Positie-1);
        AnsiString Nieuw = OpenMemo1->Lines->Strings[tel1];

        //Tenzij ook in ander memo, dan combineren.
        for (int tel2 = 0; tel2<max2 ; tel2++)
                {

                        String2 = OpenMemo2->Lines->Strings[tel2].SubString(1,Positie-1);


                        if (String1==String2)
                                {
                                Nieuw = OpenMemo1->Lines->Strings[tel1]+";"+OpenMemo2->Lines->Strings[tel2];
                                }

                } //end for2
        SaveMemo->Lines->Add(Nieuw);
        } //end for1


OpenMemo1->Clear();
OpenMemo1->Lines=SaveMemo->Lines;
SaveMemo->Clear();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::CombineButton2Click(TObject *Sender)
{
//Voegt gegevens uit andere lijst achter gegevens in deze lijst.
//Via dubbele For-loop:
int Positie = OpenMemo1->Lines->Strings[1].AnsiPos(";");

if (DifferentBox->Checked==true)
        {
        Positie=ValueField->Text.ToIntDef(0);
        }

int max1 = OpenMemo1->Lines->Count;
int max2 = OpenMemo2->Lines->Count;

AnsiString String1;
AnsiString String2;

SaveMemo->Clear();

//Dubbele forloop
for (int tel2 = 0; tel2<max2 ; tel2++)
        {
        //Default is regels toevoegen uit eigen memo
        String2 = OpenMemo2->Lines->Strings[tel2].SubString(1,Positie-1);
        AnsiString Nieuw = OpenMemo2->Lines->Strings[tel2];

        //Tenzij ook in ander memo, dan combineren.
        for (int tel1 = 0; tel1<max1 ; tel1++)
                {

                        String1 = OpenMemo1->Lines->Strings[tel1].SubString(1,Positie-1);


                        if (String1==String2)
                                {
                                Nieuw = OpenMemo2->Lines->Strings[tel2]+";"+OpenMemo1->Lines->Strings[tel1];
                                }

                } //end for2
        SaveMemo->Lines->Add(Nieuw);
        } //end for1
OpenMemo2->Clear();
OpenMemo2->Lines=SaveMemo->Lines;
SaveMemo->Clear();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::DubbelButton1Click(TObject *Sender)
{
//Verwijdert dubbelen uit deze lijst
int Positie = OpenMemo1->Lines->Strings[1].AnsiPos(";");

if (DifferentBox->Checked==true)
        {
        Positie=ValueField->Text.ToIntDef(0);
        }

int max1 = OpenMemo1->Lines->Count;
AnsiString String1;
AnsiString String2;

for (int tel1=0;tel1<max1;tel1++)
        {
        String1 = OpenMemo1->Lines->Strings[tel1].SubString(1,Positie-1);
        for (int tel2=0;tel2<max1;tel2++)
                {
                String2 = OpenMemo1->Lines->Strings[tel2].SubString(1,Positie-1);
                if (tel1!=tel2)
                        {
                        if (String1==String2)
                                {
                                OpenMemo1->Lines->Delete(tel2);
                                }
                        }
                }
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::DubbelButton2Click(TObject *Sender)
{
//Verwijdert dubbelen uit deze lijst
int Positie = OpenMemo2->Lines->Strings[1].AnsiPos(";");

if (DifferentBox->Checked==true)
        {
        Positie=ValueField->Text.ToIntDef(0);
        }

int max1 = OpenMemo2->Lines->Count;
AnsiString String1;
AnsiString String2;

for (int tel1=0;tel1<max1;tel1++)
        {
        String1 = OpenMemo2->Lines->Strings[tel1].SubString(1,Positie-1);
        for (int tel2=0;tel2<max1;tel2++)
                {
                String2 = OpenMemo2->Lines->Strings[tel2].SubString(1,Positie-1);
                if (tel1!=tel2)
                        {
                        if (String1==String2)
                                {
                                OpenMemo2->Lines->Delete(tel2);
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
//geavanceerd menu tonen
AdvancedPanel->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HideButtonClick(TObject *Sender)
{
AdvancedPanel->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DetermineButtonClick(TObject *Sender)
{
int Positie = OpenMemo1->Lines->Strings[1].AnsiPos(";");
String Joost=Positie;

AnsiPosLabel->Caption="De AnsiPos is "+Joost;
AnsiPosLabel->Show();
}
//---------------------------------------------------------------------------


