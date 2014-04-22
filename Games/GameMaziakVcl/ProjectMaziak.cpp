//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormMaziakInstructions.cpp", FormMaziakInstructions);
USEFORM("UnitFormMaziakMenu.cpp", FormMaziakMenu);
USEFORM("UnitFormMaziakGame.cpp", FormMaziakGame);
USEFORM("UnitFormMaziakGameOver.cpp", FormMaziakGameOver);
USEFORM("UnitFormMaziakGameWon.cpp", FormMaziakGameWon);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
USEFORM("UnitFormMaziakAbout.cpp", FormMaziakAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Maziak";
                 Application->CreateForm(__classid(TFormMaziakMenu), &FormMaziakMenu);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
