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
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
USEFORM("UnitFormAdditionalCopyright.cpp", FormAdditionalCopyright);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Met Z'n Drieën";
                 Application->CreateForm(__classid(TFormMenu), &FormMenu);
                 Application->CreateForm(__classid(TFormSprites), &FormSprites);
                 Application->CreateForm(__classid(TFormWhatsNew), &FormWhatsNew);
                 Application->CreateForm(__classid(TFormAdditionalCopyright), &FormAdditionalCopyright);
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
