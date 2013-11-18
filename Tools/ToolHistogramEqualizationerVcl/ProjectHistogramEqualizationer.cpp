//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitFormHistogramEqualizationer.cpp", FormHistogramEqualizationer);
USEFORM("UnitFormHistogramEqualizationerAbout.cpp", FormHistogramEqualizationerAbout);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "HistogramEqualizationer";
                 Application->CreateForm(__classid(TFormHistogramEqualizationer), &FormHistogramEqualizationer);
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
