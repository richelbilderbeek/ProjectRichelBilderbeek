//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSearchAndDestroyChess2.cpp", FormSearchAndDestroyChess2);
USEFORM("UnitFormPressKey.cpp", FormPressKey);
USEFORM("UnitFormAbout.cpp", FormAbout);
USEFORM("UnitFormSearchAndDestroyChess2Menu.cpp", FormSearchAndDestroyChessMenu);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Search And Destroy Chess 2";
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
