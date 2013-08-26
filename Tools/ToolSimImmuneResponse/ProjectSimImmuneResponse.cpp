//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormSimImmuneResponseAbout.cpp", FormSimImmuneResponseAbout);
USEFORM("UnitFormSimImmuneResponseFeedback.cpp", FormSimImmuneResponseFeedback);
USEFORM("UnitFormSimImmuneResponseInfo.cpp", FormSimImmuneResponseInfo);
USEFORM("UnitFormSimImmuneResponseLegend.cpp", FormSimImmuneResponseLegend);
USEFORM("UnitFormSimImmuneResponseMain.cpp", FormSimImmuneResponseMain);
USEFORM("UnitFormSimImmuneResponseOptions.cpp", FormSimImmuneResponseOptions);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "SimImmuneResponse";
                 Application->CreateForm(__classid(TFormSimImmuneResponseMain), &FormSimImmuneResponseMain);
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
