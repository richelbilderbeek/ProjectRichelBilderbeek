#include "qttestconceptmapwidgetdialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QPushButton>
#include <QMouseEvent>

#include "conceptmapfactory.h"

#include "conceptmapcommand.h"
#include "conceptmapcommandfactory.h"
#include "qtconceptmapwidget.h"
#include "qtdisplayconceptmap.h"
#include "qteditconceptmap.h"
#include "qtrateconceptmap.h"
#include "trace.h"
#include "ui_qttestconceptmapwidgetdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestConceptMapWidgetDialog::QtTestConceptMapWidgetDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestConceptMapWidgetDialog),
    m_buttons{},
    m_qtwidget(CreateWidget())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  //Add the three conceptmap widgets

  {
    QFrame * const frame = ui->frame_edit;
    assert(frame);
    assert(!frame->layout());
    QLayout * const layout = new QGridLayout;
    frame->setLayout(layout);

    const boost::shared_ptr<QtConceptMapWidget> widget = m_qtwidget;
    assert(widget);
    layout->addWidget(widget.get());

    assert(frame->layout());
  }

  //Command buttons
  {
    QFrame * const frame = ui->frame_buttons;
    assert(frame);
    assert(frame->layout());
    QLayout * const layout = frame->layout();
    //frame->setLayout(layout);
    //assert(frame->layout());

    for (boost::shared_ptr<ribi::cmap::Command> command: CommandFactory::CreateTestCommands())
    {
      QPushButton * const button = new QPushButton(this);
      m_buttons.push_back(button);
      button->setText(command->ToStr().c_str());
      layout->addWidget(button);
      QObject::connect(button,SIGNAL(clicked),this,SLOT(OnClick));
    }

    assert(m_buttons.size() == CommandFactory::CreateTestCommands().size());
    m_buttons[0]->setFocus();
  }
}

ribi::cmap::QtTestConceptMapWidgetDialog::~QtTestConceptMapWidgetDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::cmap::QtConceptMapWidget>
  ribi::cmap::QtTestConceptMapWidgetDialog::CreateWidget() noexcept
{
  //Each Widget must have its own ConceptMap
  /*
  std::vector<boost::shared_ptr<QtConceptMapWidget>> v;
  //Display
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::GetHeteromorphousTestConceptMaps()[17] };
    assert(m);
    const boost::shared_ptr<QtConceptMap> c(new QtDisplayConceptMap(m));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c));
    v.push_back(w);
  }
  */
  //Edit
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::GetHeteromorphousTestConceptMaps()[0] };
    assert(m);
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(m,QtEditConceptMap::Mode::simple));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c));
    return w;
    //v.push_back(w);
  }
  /*
  //Rate
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::GetHeteromorphousTestConceptMaps()[17] };
    assert(m);
    const boost::shared_ptr<QtConceptMap> c(new QtRateConceptMap(m));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c));
    v.push_back(w);
  }
  assert(v.size() == 3 && "There are three display strategies of QtConceptMap");
  return v;
  */
}


void ribi::cmap::QtTestConceptMapWidgetDialog::DoClick(const int button_index)
{
  assert(button_index >= 0);
  assert(button_index < GetNumberOfButtons());
  assert(button_index < static_cast<int>(m_buttons.size()));
  const QPushButton * const button =  m_buttons[button_index];
  const std::string text = button->text().toStdString();

  {
    const std::vector<boost::shared_ptr<Command>> commands(CommandFactory::CreateTestCommands());
    const auto command_iter = std::find_if(commands.begin(),commands.end(),
      [text](boost::shared_ptr<Command> command)
      {
        assert(command);
        return command->ToStr() == text;
      }
    );
    assert(command_iter != commands.end());
    assert(*command_iter);
    assert(m_qtwidget);
    if (m_qtwidget->CanDoCommand(*command_iter))
    {
      m_qtwidget->DoCommand(*command_iter);
    }
    else
    {
      //Nothing
    }
  }
}

void ribi::cmap::QtTestConceptMapWidgetDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); return; }
  m_qtwidget->keyPressEvent(e);
}

void ribi::cmap::QtTestConceptMapWidgetDialog::mouseDoubleClickEvent(QMouseEvent * e)
{
  m_qtwidget->mouseDoubleClickEvent(e);
}

void ribi::cmap::QtTestConceptMapWidgetDialog::mouseMoveEvent(QMouseEvent * e)
{
  m_qtwidget->mouseMoveEvent(e);
}

void ribi::cmap::QtTestConceptMapWidgetDialog::mousePressEvent(QMouseEvent * e)
{
  m_qtwidget->mousePressEvent(e);
}

void ribi::cmap::QtTestConceptMapWidgetDialog::OnClick()
{
  TRACE_FUNC();
  const auto button_iter = std::find_if(m_buttons.begin(),m_buttons.end(),
    [](QPushButton * const button) { return button->hasFocus(); }
  );
  if (button_iter == m_buttons.end()) return;
  const int button_index {
    static_cast<int>(
      std::distance(
        m_buttons.begin(),
        button_iter
      )
    )
  };
  assert(button_index >= 0);
  assert(button_index < static_cast<int>(m_buttons.size()));
  DoClick(button_index);
}

#ifndef NDEBUG
void ribi::cmap::QtTestConceptMapWidgetDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtTestConceptMapWidgetDialog::Test");
  TRACE("Clicking once");
  {
    const QtTestConceptMapWidgetDialog tmp;
    const int j = tmp.GetNumberOfButtons();
    for (int i=0; i!=j; ++i)
    {
      QtTestConceptMapWidgetDialog d;
      //d.show();
      d.DoClick(i);
    }
  }
  TRACE("Clicking twice");
  {
    const QtTestConceptMapWidgetDialog tmp;
    const int sz = tmp.GetNumberOfButtons();
    for (int i=0; i!=sz; ++i)
    {
      for (int j=0; j!=sz; ++j)
      {
        QtTestConceptMapWidgetDialog d;
        //d.show();
        d.DoClick(i);
        d.DoClick(j);
      }
    }
  }
  TRACE("Clicking thrice");
  {
    const QtTestConceptMapWidgetDialog tmp;
    const int sz = tmp.GetNumberOfButtons();
    for (int i=0; i!=sz; ++i)
    {
      for (int j=0; j!=sz; ++j)
      {
        for (int k=0; k!=sz; ++k)
        {
          QtTestConceptMapWidgetDialog d;
          //d.show();
          d.DoClick(i);
          d.DoClick(j);
          d.DoClick(k);
        }
      }
    }
  }
  TRACE("Clicking four times");
  {
    const QtTestConceptMapWidgetDialog tmp;
    const int sz = tmp.GetNumberOfButtons();
    for (int i=0; i!=sz; ++i)
    {
      for (int j=0; j!=sz; ++j)
      {
        for (int k=0; k!=sz; ++k)
        {
          for (int m=0; m!=sz; ++m)
          {
            QtTestConceptMapWidgetDialog d;
            //d.show();
            d.DoClick(i);
            d.DoClick(j);
            d.DoClick(k);
            d.DoClick(m);
          }
        }
      }
    }
  }
  TRACE("Random clicking");
  {
    QtTestConceptMapWidgetDialog d;
    //d.show();
    const int n_buttons = d.GetNumberOfButtons();
    for (int i=0; i!=100; ++i)
    {
      d.DoClick(std::rand() % n_buttons);
    }
  }
  TRACE("Finished ribi::cmap::QtTestConceptMapWidgetDialog::Test successfully");
}
#endif
