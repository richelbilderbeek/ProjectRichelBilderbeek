//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormClassicTronGame.cpp", FormClassicTronGame);
USEFORM("UnitFormClassicTronMenu.cpp", FormClassicTronMenu);
USEFORM("UnitFormPressKey.cpp", FormPressKey);
USEFORM("UnitFormSelectColor.cpp", FormSelectColor);
USEFORM("UnitFormChart.cpp", FormChart);
USEFORM("UnitFormClassicTronAbout.cpp", FormClassicTronAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Classic Tron";
                 Application->CreateForm(__classid(TFormClassicTronMenu), &FormClassicTronMenu);
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
