//---------------------------------------------------------------------------

#ifndef UnitFormChartH
#define UnitFormChartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TFormLineChart : public TForm
{
__published:	// IDE-managed Components
        TChart *mChart;
        TFastLineSeries *Series1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormLineChart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLineChart *FormLineChart;
//---------------------------------------------------------------------------
#endif
