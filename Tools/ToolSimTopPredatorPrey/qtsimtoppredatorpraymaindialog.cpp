#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtsimtoppredatorpraymaindialog.h"

#include <cassert>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QTimer>
#include "ui_qtsimtoppredatorpraymaindialog.h"

#include "qtfractionimage.h"
#pragma GCC diagnostic pop

QtSimTopPredatorPrayMainDialog::QtSimTopPredatorPrayMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSimTopPredatorPrayMainDialog),
    m_widget_prey{new QtFractionImage},
    m_widget_pred{new QtFractionImage},
    m_widget_top{new QtFractionImage},
    m_grid_prey{CreateGrid()},
    m_grid_pred{CreateGrid()},
    m_grid_top{CreateGrid()}
{
  ui->setupUi(this);
  this->setGeometry(0,
    0,
    24 + (3 * QtFractionImage::GetWidth()),
    16 + QtFractionImage::GetHeight()
  );
  assert(!this->layout());
  QLayout * const layout = new QHBoxLayout;
  this->setLayout(layout);
  layout->addWidget(m_widget_prey);
  layout->addWidget(m_widget_pred);
  layout->addWidget(m_widget_top);

  //Put dialog at screen center
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
  }
  //Initialize the grids
  {

    const int w{QtFractionImage::GetWidth()};
    const int h{QtFractionImage::GetHeight()};
    for (int y{0}; y!=h; ++y)
    {
      for (int x{0}; x!=w; ++x)
      {
        m_grid_prey[y][x] = 0.5;
        m_grid_pred[y][x]= GetRandomUniform() < m_frac_pred ? 0.1 : 0.0;
        m_grid_top[y][x] = GetRandomUniform() < m_frac_top ? 0.1 : 0.0;
      }
    }

  }
  //Start the timer
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(0);
    timer->start();
  }
}

QtSimTopPredatorPrayMainDialog::~QtSimTopPredatorPrayMainDialog()
{
  delete ui;
}

QtSimTopPredatorPrayMainDialog::Grid QtSimTopPredatorPrayMainDialog::CreateDiffusion(const Grid& grid) noexcept
{
  const int w{QtFractionImage::GetWidth()};
  const int h{QtFractionImage::GetHeight()};
  Grid diffusion{CreateGrid()};
  for (int y{0}; y!=h; ++y)
  {
    for (int x{0}; x!=w; ++x)
    {
      const int x_left  = x ==     0 ? w-1 : x-1;
      const int x_right = x == w - 1 ?   0 : x+1;
      const int y_above = y ==   0 ? h-1 : y-1;
      const int y_below = y == h-1 ?   0 : y+1;
      const double here{grid[y][x]};
      const double above{grid[y_above][x]};
      const double below{grid[y_below][x]};
      const double left{grid[y][x_left]};
      const double right{grid[y][x_right]};
      diffusion[y][x] =
        (
          (
              (above - here)
            + (right - here)
            + (below - here)
            + (left - here)
          )
          * m_diffusion_coefficient
        );
    }
  }
  return diffusion;
}

QtSimTopPredatorPrayMainDialog::Grid QtSimTopPredatorPrayMainDialog::CreateGrid() noexcept
{
  return {static_cast<std::size_t>(QtFractionImage::GetHeight()),
      std::vector<double>(QtFractionImage::GetWidth(),0.0)
  };
}

double QtSimTopPredatorPrayMainDialog::GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}

double QtSimTopPredatorPrayMainDialog::Limit(const double x)
{
  if (x < 0.0) return 0.0;
  if (x > 1.0) return 1.0;
  return x;
}

void QtSimTopPredatorPrayMainDialog::OnTimer() noexcept
{
  const int w{QtFractionImage::GetWidth()};
  const int h{QtFractionImage::GetHeight()};

  const Grid prey_diffuse{CreateDiffusion(m_grid_prey)};
  const Grid pred_diffuse{CreateDiffusion(m_grid_pred)};
  const Grid top_diffuse{CreateDiffusion(m_grid_top)};

  //Top-Pred-Prey interaction
  for (int y{0}; y!=h; ++y)
  {
    for (int x{0}; x!=w; ++x)
    {
      m_grid_prey[y][x] = Limit(m_grid_prey[y][x] + prey_diffuse[y][x]);
      m_grid_pred[y][x] = Limit(m_grid_pred[y][x] + pred_diffuse[y][x]);
      m_grid_top[y][x] = Limit(m_grid_top[y][x] + top_diffuse[y][x]);
    }
  }

  Grid prey_interact{CreateGrid()};
  Grid pred_interact{CreateGrid()};
  Grid top_interact{CreateGrid()};
  for (int y{0}; y!=h; ++y)
  {
    for (int x{0}; x!=w; ++x)
    {
      const double prey{m_grid_prey[y][x]};
      const double pred{m_grid_pred[y][x]};
      const double top{m_grid_top[y][x]};
      assert(prey >= 0.0);
      assert(pred >= 0.0);
      assert(top >= 0.0);
      assert(prey <= 1.0);
      assert(pred <= 1.0);
      assert(top <= 1.0);
      const double pred_efficiency{0.5};
      const double top_efficiency{0.5};
      //const double r_prey{10.0};
      const double prey_growth{prey * (1.0 - prey)};
      const double prey_eaten{prey*pred*pred_efficiency/(1.0 + (pred_efficiency*prey))};
      const double pred_growth{prey_eaten*0.2};
      const double pred_eaten{pred*top*top_efficiency/(1.0 + (top_efficiency*pred))};
      const double top_growth{pred_eaten*0.1};
      const double top_eaten{0.0};
      const double new_prey{prey + prey_growth - prey_eaten};
      const double new_pred{pred + pred_growth - pred_eaten};
      const double new_top { top +  top_growth -  top_eaten};
      assert(new_prey >= -0.1);
      assert(new_pred >= -0.1);
      assert(new_top >= -0.1);
      assert(new_prey <= 1.1);
      assert(new_pred <= 1.1);
      assert(new_top <= 1.1);
      prey_interact[y][x] = Limit(new_prey);
      pred_interact[y][x] = Limit(new_pred);
      top_interact[y][x] = Limit(new_top);
    }
  }


  //Top-Pred-Prey interaction
  for (int y{0}; y!=h; ++y)
  {
    for (int x{0}; x!=w; ++x)
    {
      m_grid_prey[y][x] = prey_interact[y][x];
      m_grid_pred[y][x] = pred_interact[y][x];
      m_grid_top[y][x] = top_interact[y][x];
    }
  }

  m_widget_prey->Set(m_grid_prey);
  m_widget_pred->Set(m_grid_pred);
  m_widget_top->Set(m_grid_top);
}
