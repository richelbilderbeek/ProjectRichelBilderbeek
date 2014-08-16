//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSuperTronMenu.cpp", FormSuperTronMenu);
USEFORM("UnitFormPressKey.cpp", FormPressKey);
USEFORM("UnitFormSelectColor.cpp", FormSelectColor);
USEFORM("UnitFormChart.cpp", FormChart);
USEFORM("UnitFormSuperTronAbout.cpp", FormSuperTronAbout);
USEFORM("UnitFormSuperTronGame.cpp", FormSuperTronGame);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Super Turbo";
     Application->CreateForm(__classid(TFormSuperTronMenu), &FormSuperTronMenu);
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
