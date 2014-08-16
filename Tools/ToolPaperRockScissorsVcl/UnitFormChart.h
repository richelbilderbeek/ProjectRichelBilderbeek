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
class TFormChart : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TFastLineSeries *Series1;
        TFastLineSeries *Series2;
        TFastLineSeries *Series3;
private:	// User declarations
public:		// User declarations
        __fastcall TFormChart(TComponent* Owner);
        void Add(const double p, const double r, const double s);
        void Clear();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormChart *FormChart;
//---------------------------------------------------------------------------
#endif
