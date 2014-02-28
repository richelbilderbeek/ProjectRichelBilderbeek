#include "staircasecard.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <cassert>

#include "textcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::scc::StaircaseCard::StaircaseCard(const int n_cols, const int n_rows)
  : m_v(CreateGrid(n_cols,n_rows))
{
}

const std::vector<ribi::scc::Column> ribi::scc::StaircaseCard::CreateGrid(const int n_cols, const int n_rows) noexcept
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

const boost::shared_ptr<ribi::TextCanvas> ribi::scc::StaircaseCard::ToTextCanvas() const noexcept
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


  */

  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(width,height)
  };

  for (int y=0; y!=height; ++y)
  {
    if (y % 2 == 0)
    {
      canvas->PutText(0,y,std::string(width,'-'));
    }
    else
    {
      for (int x=0; x!=width; ++x)
      {
        if (x % 2 == 0)
        {
          //Put space, unless between h and v
          canvas->PutChar(x,y,' ');
          if (x <= 2 || x >= width - 2) continue;
          const int col { (y - 1) / 2 };
          const int row_left { (x - 2) / 2 };
          const int row_right { row_left + 1 };
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
          canvas->PutChar(
            x,
            y,
            m_v[col].GetOrientation(row) == Orientation::horizontal ? 'h' : 'v'
          );
        }
      }
    }
  }
  return canvas;
}

const boost::shared_ptr<ribi::TextCanvas> ribi::scc::StaircaseCard::ToTextCanvasCompact() const noexcept
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
