//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormReversi.cpp", FormReversi);
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormRestart.cpp", FormRestart);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Reversi";
                 Application->CreateForm(__classid(TFormReversi), &FormReversi);
                 Application->CreateForm(__classid(TFormRestart), &FormRestart);
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
