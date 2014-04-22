//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSpaceHarryGame.cpp", FormSpaceHarryGame);
USEFORM("UnitFormSpaceHarryGameOver.cpp", FormSpaceHarryGameOver);
USEFORM("UnitFormSpaceHarryMenu.cpp", FormSpaceHarryMenu);
USEFORM("UnitFormSpaceHarryAbout.cpp", FormSpaceHarryAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Space Harry";
                 Application->CreateForm(__classid(TFormSpaceHarryMenu), &FormSpaceHarryMenu);
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
