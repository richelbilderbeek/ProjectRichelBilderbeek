//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormTronCollectionMenu.cpp", FormTronCollectionMenu);
USEFORM("UnitFormClassicTronAbout.cpp", FormClassicTronAbout);
USEFORM("UnitFormClassicTronGame.cpp", FormClassicTronGame);
USEFORM("UnitFormClassicTronMenu.cpp", FormClassicTronMenu);
USEFORM("UnitFormSuperTronAbout.cpp", FormSuperTronAbout);
USEFORM("UnitFormSuperTronGame.cpp", FormSuperTronGame);
USEFORM("UnitFormSuperTronMenu.cpp", FormSuperTronMenu);
USEFORM("UnitFormChart.cpp", FormChart);
USEFORM("UnitFormPressKey.cpp", FormPressKey);
USEFORM("UnitFormSelectColor.cpp", FormSelectColor);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "The Tron Collection";
                 Application->CreateForm(__classid(TFormTronCollectionMenu), &FormTronCollectionMenu);
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
