//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormBarbaImageMain.cpp", FormBarbaImageMain);
USEFORM("UnitFormImage.cpp", FormImage);
USEFORM("UnitFormStringGrid.cpp", FormStringGrid);
USEFORM("UnitFormBarbaImageAbout.cpp", FormBarbaImageAbout);
USEFORM("UnitFormTrackBar.cpp", FormTrackBar);
USEFORM("UnitFormWhatsNew.cpp", FormWhatsNew);
USEFORM("UnitFormBarbaImageWhatsNew.cpp", FormBarbaImageWhatsNew);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "BarbaImage";
                 Application->CreateForm(__classid(TFormBarbaImageMain), &FormBarbaImageMain);
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
