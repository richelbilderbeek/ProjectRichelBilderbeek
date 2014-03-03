#include "staircasecard.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include <QImage>

#include "textcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::scc::StaircaseCard::StaircaseCard(const int n_cols, const int n_rows)
  : m_v(CreateGrid(n_cols,n_rows))
{

}

std::vector<int> ribi::scc::StaircaseCard::ColumnToMap(const Column& c) noexcept
{
  const int sz { c.GetMax() };
  std::vector<int> v(sz,0);
  int horizontal = -1;
  int vertical = 1;
  for (int i=0; i!=sz; ++i)
  {
    switch (c.GetOrientation(i))
    {
      case Orientation::horizontal: v[i] = horizontal; --horizontal; break;
      case Orientation::vertical  : v[i] = vertical  ; ++vertical  ; break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("ribi::scc::StaircaseCard::ColumnToMap: invalid orientation");
    }
  }
  return v;
}

std::vector<ribi::scc::Column> ribi::scc::StaircaseCard::CreateGrid(const int n_cols, const int n_rows) noexcept
{
  std::vector<Column> v;
  v.reserve(n_cols);
  for (int i=0; i!=n_cols; ++i)
  {
    const int a = n_rows / 2;
    const int b = n_rows - a;
    assert(a + b == n_rows);
    Column c(a,b);
    v.push_back(c);
  }
  return v;
}

boost::shared_ptr<ribi::scc::StaircaseCard> ribi::scc::StaircaseCard::GetTest(const int i) noexcept
{
  std::vector<Column> v;

  switch(i)
  {
    case 0:
    {
      /*

      0  vvvhh
      1  vhvvh
      2  vvhvh
      3  vvvhh
         01234

         01234567890
      0  -----------
      1   v v v|h h
      2  -----------
      3   v|h|v v|h
      4  -----------
      5   v v|h|v|h
      6  -----------
      7   v v v|h h
      8  -----------

      */

      v.push_back(Column(3,2));
      v.push_back(Column( { 1,1,2,1 }));
      v.push_back(Column( { 2,1,1,1 }));
      v.push_back(Column(3,2));
      break;
    }
    default:
      assert(!"Should not get here");
      throw std::logic_error("ribi::scc::StaircaseCard::GetTes: unknown test index");
  }

  boost::shared_ptr<StaircaseCard> card {
    new StaircaseCard(v)
  };
  assert(card);
  return card;

}

boost::shared_ptr<QImage> ribi::scc::StaircaseCard::ToImage() const noexcept
{
  const boost::shared_ptr<TextCanvas> canvas {
    ToTextCanvas()
  };
  assert(canvas);
  const int width { canvas->GetWidth() };
  const int height { canvas->GetHeight() };
  boost::shared_ptr<QImage> image {
    new QImage(width,height,QImage::Format_ARGB32)
  };
  assert(image);
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      image->setPixel(x,y,
        canvas->GetChar(x,y) == ' ' ? qRgb(255,255,255) : qRgb(0,0,0)
      );
    }
  }
  return image;
}


boost::shared_ptr<ribi::TextCanvas> ribi::scc::StaircaseCard::ToTextCanvas() const noexcept
{
  const int height { (static_cast<int>(m_v.size()) * 2) + 1 };
  assert(height > 0);
  const int width { (static_cast<int>(m_v[0].GetMax()) * 2) + 1 };
  assert(width > 0);

  /*
0  vvvhh
1  vhvvh
2  vvhvh
3  vvvhh
   01234

   01234567890
0  -----------
1   v v v|h h
2  -----------
3   v|h|v v|h
4  -----------
5   v v|h|v|h
6  -----------
7   v v v|h h
8  -----------


 01234567890
0      +
1      |
2  +-+-+-+
3  | |   |
4  +-+-+ +
5    | | |
6    +-+-+
7      |
8      +

  */

  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(width,height)
  };

  for (int y=0; y!=height; ++y)
  {
    if (y % 2 == 0)
    {
      //canvas->PutText(0,y,std::string(width,'-'));
    }
    else
    {
      for (int x=0; x!=width; ++x)
      {
        if (x % 2 == 0)
        {
          //Put space, unless between h and v
          canvas->PutChar(x,y,' ');
          //if (x <= 2 || x >= width - 2) continue;
          const int col { (y - 1) / 2 };
          const int row_left { (x - 2) / 2 };
          const int row_right { row_left + 1 };
          if (row_left < 0) continue;
          if (row_right >= m_v[col].GetMax()) continue;
          assert(col >= 0);
          assert(col < static_cast<int>(m_v.size()));
          assert(row_left >= 0);
          assert(row_left < m_v[col].GetMax());
          assert(row_right >= 0);
          assert(row_right < m_v[col].GetMax());
          if (m_v[col].GetOrientation(row_left) != m_v[col].GetOrientation(row_right))
          {
            canvas->PutChar(x,y,'|');
          }
        }
        else
        {
          const int col { (y - 1) / 2 };
          const int row { (x - 1) / 2 };
          assert(col >= 0);
          assert(col < static_cast<int>(m_v.size()));
          assert(row >= 0);
          assert(row < m_v[col].GetMax());
          //Put h/v
          //canvas->PutChar(
          //  x,
          //  y,
          //  m_v[col].GetOrientation(row) == Orientation::horizontal ? 'h' : 'v'
          //);
        }
      }
    }
  }

  //Vertical lines
  const int n_cols { static_cast<int>(m_v.size()) };
  const int n_rows { m_v[0].GetMax() };
  for (int y=0; y!=n_cols-1; ++y)
  {
    assert(m_v[y].GetMax() == m_v[y+1].GetMax());
    const std::vector<int> a { ColumnToMap(m_v[y  ]) };
    const std::vector<int> b { ColumnToMap(m_v[y+1]) };
    for (int x=0; x!=n_rows; ++x)
    {
      canvas->PutChar(
        (x * 2) + 1 - 0,
        (y * 2) + 1 + 1,
        a[x] == b[x] ? ' ' : '-'
      );
    }

  }

  for (int y=0; y!=height; ++y)
  {
    if (y % 2) continue;
    for (int x=0; x!=width; ++x)
    {
      if (x % 2) continue;
      if (
           (x+1 < width && canvas->GetChar(x+1,y) != ' ')
        || (y+1 < height && canvas->GetChar(x,y+1) != ' ')
        || (x-1 > 0 && canvas->GetChar(x-1,y) != ' ')
        || (y-1 > 0 && canvas->GetChar(x,y-1) != ' ')
      )
      {
        canvas->PutChar(x,y,'+');
      }
    }
  }

  return canvas;
}

boost::shared_ptr<ribi::TextCanvas> ribi::scc::StaircaseCard::ToTextCanvasCompact() const noexcept
{
  const int height { static_cast<int>(m_v.size()) };
  assert(height > 0);
  const int width { static_cast<int>(m_v[0].GetMax()) };
  assert(width > 0);

  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(width,height)
  };

  for (int y=0; y!=height; ++y)
  {
    canvas->PutText(0,y,m_v[y].ToStr());
  }
  return canvas;
}
