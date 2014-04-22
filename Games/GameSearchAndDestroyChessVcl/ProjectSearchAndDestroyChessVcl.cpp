//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSearchAndDestroyChess.cpp", FormSearchAndDestroyChess);
USEFORM("UnitFormPressKey.cpp", FormPressKey);
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormSearchAndDestroyChessMenu.cpp", FormSearchAndDestroyChessMenu);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Search And Destroy Chess";
                 Application->CreateForm(__classid(TFormSearchAndDestroyChessMenu), &FormSearchAndDestroyChessMenu);
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
