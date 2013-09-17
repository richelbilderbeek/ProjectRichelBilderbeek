//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormMain.cpp", FormMain);
USEFORM("UnitFormMenu.cpp", FormMenu);
USEFORM("UnitFormGewonnen.cpp", FormGewonnen);
USEFORM("UnitFormStoppen.cpp", FormStoppen);
USEFORM("UnitFormOver.cpp", FormOver);
USEFORM("UnitFormSpelregels.cpp", FormSpelregels);
USEFORM("UnitFormSprites.cpp", FormSprites);
USEFORM("UnitFormCopyrightK3.cpp", FormCopyrightK3);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "K3 Op Een Rij";
                 Application->CreateForm(__classid(TFormMenu), &FormMenu);
                 Application->CreateForm(__classid(TFormSprites), &FormSprites);
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
