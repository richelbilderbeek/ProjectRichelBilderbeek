#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtfilteroperationermaindialog.h"
#include "ui_qtfilteroperationermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtFilterOperationerMainDialog::QtFilterOperationerMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtFilterOperationerMainDialog)
{
  ui->setupUi(this);
}

ribi::QtFilterOperationerMainDialog::~QtFilterOperationerMainDialog()
{
  delete ui;
}

/*

__fastcall TFormFilterOperationer::TFormFilterOperationer(TComponent* Owner)
        : TForm(Owner)
{
  //A vertical edge detection filter
  StringGridFilter->Cells[0][0] = -1.0;
  StringGridFilter->Cells[1][0] =  0.0;
  StringGridFilter->Cells[2][0] =  1.0;
  StringGridFilter->Cells[0][1] = -1.0;
  StringGridFilter->Cells[1][1] =  0.0;
  StringGridFilter->Cells[2][1] =  1.0;
  StringGridFilter->Cells[0][2] = -1.0;
  StringGridFilter->Cells[1][2] =  0.0;
  StringGridFilter->Cells[2][2] =  1.0;
}

void __fastcall TFormFilterOperationer::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute()==false) return;
  ImageSource->Picture->LoadFromFile(OpenDialog1->FileName);
  ImageSource->Visible = true;
  OnStringGridFilterChange(0);
  ++PageControl->ActivePageIndex;
}

void __fastcall TFormFilterOperationer::OnStringGridFilterChange2(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
  OnStringGridFilterChange(0);
}

void __fastcall TFormFilterOperationer::OnStringGridFilterChange(
      TObject *Sender)
{
  ButtonDo->Enabled = CanDoFilterOperation(ImageSource, StringGridFilter, ImageTarget);
}

void __fastcall TFormFilterOperationer::ButtonDoClick(TObject *Sender)
{
  //Check StringGrid for valid strings
  assert(CanDoFilterOperation(ImageSource, StringGridFilter, ImageTarget)==true);

  //Convert StringGrid to std::vector and then the other way round,
  //to clean up the StringGrid after lousy input
  {
    const std::vector<std::vector<double> > v = StringGridToVector<double>(StringGridFilter);
    assert(v.empty()==false);
    const int maxy = v.size();
    assert(maxy>0);
    const int maxx = v[0].size();
    assert(maxx>0);
    for (int y=0; y!=maxy; ++y)
    {
      for (int x=0; x!=maxx; ++x)
      {
        StringGridFilter->Cells[x][y] = v[y][x];
      }
    }
  }

  DoFilterOperation(ImageSource, StringGridFilter, ImageTarget);
  ImageTarget->Visible = true;
  ImageTarget->Refresh();
  ButtonSaveResult->Enabled = true;
  ButtonEnhance->Enabled = true;
  ++PageControl->ActivePageIndex;

}

void __fastcall TFormFilterOperationer::ButtonEnhanceClick(TObject *Sender)
{
  ImageEnhanced->Picture->Graphic = ImageTarget->Picture->Graphic;

  #ifndef NDEBUG
    const double averageGreynessOld = GetAverageGreyness(ImageEnhanced);
  #endif

  EnhanceContrast(ImageEnhanced);

  #ifndef NDEBUG
    const double averageGreynessNew = GetAverageGreyness(ImageEnhanced);
    assert( std::fabs(averageGreynessOld - averageGreynessNew) < 1.0 );
  #endif

  ImageEnhanced->Visible = true;
  ImageEnhanced->Refresh();
  ButtonSaveEnhanced->Enabled = true;
  ++PageControl->ActivePageIndex;

}

void __fastcall TFormFilterOperationer::ButtonSaveResultClick(TObject *Sender)
{
  if (SaveDialog1->Execute()==false) return;
  ImageTarget->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("Image saved successfully");
  PageControl->ActivePageIndex+=2;
}

void __fastcall TFormFilterOperationer::ItemAddColClick(TObject *Sender)
{
  ++StringGridFilter->ColCount;
}

void __fastcall TFormFilterOperationer::ItemAddRowClick(TObject *Sender)
{
  ++StringGridFilter->RowCount;
}

void __fastcall TFormFilterOperationer::ItemRemoveColClick(TObject *Sender)
{
  if (StringGridFilter->ColCount > 1) --StringGridFilter->ColCount;
}

void __fastcall TFormFilterOperationer::ItemRemoveRowClick(TObject *Sender)
{
  if (StringGridFilter->RowCount > 1) --StringGridFilter->RowCount;
}

void __fastcall TFormFilterOperationer::ButtonSaveEnhancedClick(
      TObject *Sender)
{
  if (SaveDialog1->Execute()==false) return;
  ImageEnhanced->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("Image saved successfully");
  ++PageControl->ActivePageIndex;
}

void __fastcall TFormFilterOperationer::PanelAbout3Click(TObject *Sender)
{
  ImageSource->Picture = ImageRichel->Picture;
  ImageSource->Refresh();
  ImageSource->Visible = true;
  ButtonDo->Enabled = true;
  PageControl->ActivePageIndex = 0;
}

const bool CanDoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGridFilter,
  TImage * const imageTarget)
{
  if (imageSource == 0) return false;
  if (imageSource->Picture->Bitmap == 0) return false;
  if (imageSource->Picture->Bitmap->PixelFormat != pf24bit) return false;
  if (stringGridFilter == 0) return false;
  if (imageTarget == 0) return false;
  if (imageTarget->Picture->Bitmap == 0) return false;
  if (imageTarget->Picture->Bitmap->PixelFormat != pf24bit) return false;
  if (stringGridFilter->ColCount < 1) return false;
  if (stringGridFilter->RowCount < 1) return false;
  if (stringGridFilter->ColCount == 1 && stringGridFilter->RowCount == 1) return false;

  if (CanStringGridToVector<double>(stringGridFilter) == false) return false;

  //Does the filter yield a valid filter range?
  const std::vector<std::vector<double> > filter = StringGridToVector<double>(stringGridFilter);
  const std::pair<double,double> filterRange = GetFilterRange(filter);
  if (filterRange.first == filterRange.second) return false;
  return true;
}

void DoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGridFilter,
  TImage * const imageTarget)
{
  assert(imageSource != 0
    && "imageSource must not be NULL");
  assert(imageSource->Picture->Bitmap != 0
    && "imageSource bitmap must not be NULL");
  assert(imageSource->Picture->Bitmap->PixelFormat == pf24bit
    && "imageSource must be a 24-bit bitmap");
  assert(stringGridFilter != 0
    && "stringGridFilter must not be NULL");
  assert(imageTarget != 0
    && "imageTarget must not be NULL");
  assert(imageTarget->Picture->Bitmap != 0
    && "imageSource bitmap must not be NULL");
  assert(imageTarget->Picture->Bitmap->PixelFormat == pf24bit
    && "imageTarget must be a 24-bit bitmap");
  assert(stringGridFilter->ColCount >= 1
    && "stringGridFilter must have at least one collumn");
  assert(stringGridFilter->RowCount >= 1
    && "stringGridFilter must have at least one row");
  assert( (stringGridFilter->ColCount > 1 || stringGridFilter->RowCount > 1)
    && "stringGridFilter must be larger then 1x1 cell");
  assert(CanStringGridToVector<double>(stringGridFilter) == true
    && "stringGridFilter's content must be convertable to doubles");

  const std::vector<std::vector<int> > source = ImageToVector(imageSource);

  const std::vector<std::vector<double> > filter = StringGridToVector<double>(stringGridFilter);

  assert(!source.empty());
  assert(!filter.empty());

  #ifndef NDEBUG
  {
    const std::pair<double,double> filterRange = GetFilterRange(filter);
    assert(filterRange.first != filterRange.second && "Filter must have a valid range");
  }
  #endif

  const std::vector<std::vector<int> > result = DoFilterOperation(source,filter);
  VectorToImage(result,imageTarget);
}

//VCL dependent
//From http://www.richelbilderbeek.nl/CppStringGridToVector.htm
template <class T>
const std::vector<std::vector<T> > StringGridToVector(const TStringGrid * const stringGrid)
{
  assert(CanStringGridToVector<T>(stringGrid)==true);
  assert(stringGrid!=0 && "StringGrid must not be NULL");
  const int height = stringGrid->RowCount;
  const int width  = stringGrid->ColCount;
  std::vector<std::vector<T> > v(height,std::vector<T>(width));
  for (int y=0; y!=height; ++y)
  {
    assert(y >=0);
    assert(y < static_cast<int>(v.size()) );
    std::vector<T>& line = v[y];
    //Don't have the guts to do a line-access on a TStringGrid...

    for (int x=0; x!=width; ++x)
    {
      assert(x >=0);
      assert(x < static_cast<int>(line.size()) );
      //const_cast because the VCL is not const-correct. Grumble, grumble...
      const std::string s = (const_cast<TStringGrid*>(stringGrid)->Cells[x][y]).c_str();
      const T t = LexicalCast<T>(s);
      line[x] = t;
    }
  }
  return v;
}

//VCL dependent
//From http://www.richelbilderbeek.nl/CanStringGridToVector.htm
template <class T>
const bool CanStringGridToVector(const TStringGrid * const stringGrid)
{
  if (stringGrid==0) return false;

  const int height = stringGrid->RowCount;
  const int width  = stringGrid->ColCount;

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      //const_cast because the VCL is not const-correct. Grumble, grumble...
      const std::string s = (const_cast<TStringGrid*>(stringGrid)->Cells[x][y]).c_str();
      if (CanCast<T>(s) == false) return false;
    }
  }
  return true;
}

//VCL independent
//Creates a 2D-std::vector (y-x-ordered) from a TImage
//From http://www.richelbilderbeek.nl/CppImageToVector.htm
const std::vector<std::vector<int> > ImageToVector(const TImage * const image)
{
  assert(image!=0 && "Image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");

  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;

  std::vector<std::vector<int> > v(height,std::vector<int>(width));

  for (int y=0; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < static_cast<int>(v.size()));
    std::vector<int>& vLine = v[y];
    const unsigned char * const line
      = static_cast<const unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < static_cast<int>(vLine.size()));
      const double grey = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      vLine[x] = grey;
      assert(grey>=0.0 && grey<256.0);
    }
  }
  return v;
}

//VCL independent
//Creates a 2D-std::vector (y-x-ordered) from a TImage
//Draws a (grey) TImage from a 2D-std::vector (y-x-ordered)
//From http://www.richelbilderbeek.nl/CppVectorToImage.htm
void VectorToImage(const std::vector<std::vector<int> >& v, const TImage * const image)
{
  assert(image!=0 && "Image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");

  const int height = v.size();
  const int width  = v[0].size();

  image->Picture->Bitmap->Height = height;
  image->Picture->Bitmap->Width  = width;

  for (int y=0; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < static_cast<int>(v.size()));
    const std::vector<int>& vLine = v[y];
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < static_cast<int>(vLine.size()));
      const int grey = vLine[x];
      line[x*3+2] = grey; //Red
      line[x*3+1] = grey; //Green
      line[x*3+0] = grey; //Blue
    }
  }
}

//From http://www.richelbilderbeek.nl/CppEnhanceContrast.htm
void EnhanceContrast(const TImage * const image)
{
  //Find lowest and highest value
  assert(image!=0 && "image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "image bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "image bitmap must be 24 bit");

  //Get the width and height from the source
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double averageGreyness = GetAverageGreyness(image);

  double stretch = 1000.0; //Way too much for nearly all images

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const line
      = static_cast<const unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const double grey
        = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      const double diff = grey - averageGreyness;
      if (diff < 0.0)
      {
        //pixel was darker then average
        const double newStretch = -averageGreyness / diff;
        assert(newStretch >= 0.0);
        if (newStretch < stretch) stretch = newStretch;
      }
      else if (diff > 0.0)
      {
        //pixel was lighter then average
        const double newStretch = (255.9 - averageGreyness)  / diff;
        if (newStretch < stretch) stretch = newStretch;
      }
    }
  }

  //Enhance the contrast
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const double grey
        = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      const double diff = grey - averageGreyness;
      const double diffGreyNew = averageGreyness + (static_cast<double>(diff) * stretch);
      const int newGrey = static_cast<int>(diffGreyNew);
      assert(newGrey >=   0);
      assert(newGrey <  256);
      line[x*3+2] = newGrey; //Red
      line[x*3+1] = newGrey; //Green
      line[x*3+0] = newGrey; //Blue
    }
  }
}


//From http://www.richelbilderbeek.nl/CppGetAverageGreyness.htm
const double GetAverageGreyness(const TImage * const image)
{
  assert(image!=0 && "image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "image bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "image bitmap must be 24 bit");

  //Get the width and height from the source
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  double sum = 0.0;

  for (int y=0; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < image->Picture->Bitmap->Height);
    const unsigned char * line
      = static_cast<const unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < image->Picture->Bitmap->Width);
      const double grey
        = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      sum += grey;
    }
  }
  const int surface = width * height;
  assert(surface>0);
  const double average = sum / static_cast<double>(surface);
  assert(average >=    0.0);
  assert(average  <  256.0);
  return average;
}


*/
