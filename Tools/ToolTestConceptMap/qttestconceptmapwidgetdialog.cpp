#include "qttestconceptmapwidgetdialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QPushButton>

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
    m_commands(CommandFactory::CreateTestCommands()),
    m_qtwidgets(CreateWidgets())
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  //Add the three conceptmap widgets

  const std::vector<QFrame *> frames {
    ui->frame_display, ui->frame_edit, ui->frame_rate
  };
  assert(m_qtwidgets.size() == frames.size());
  assert(m_qtwidgets.size() == 3);
  for (int i=0; i!=3; ++i)
  {
    QFrame * const frame = frames[i];
    assert(frame);
    assert(!frame->layout());
    QLayout * const layout = new QGridLayout;
    frame->setLayout(layout);

    const boost::shared_ptr<QtConceptMapWidget> widget = m_qtwidgets[i];
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

    for (boost::shared_ptr<ribi::cmap::Command> command: m_commands)
    {
      QPushButton * const button = new QPushButton(this);
      m_buttons.push_back(button);
      button->setText(command->ToStr().c_str());
      layout->addWidget(button);
      QObject::connect(button,&QPushButton::clicked,this,&QtTestConceptMapWidgetDialog::OnClick);
    }

    assert(m_buttons.size() == m_commands.size());
  }
}

ribi::cmap::QtTestConceptMapWidgetDialog::~QtTestConceptMapWidgetDialog()
{
  delete ui;
}

const std::vector<boost::shared_ptr<ribi::cmap::QtConceptMapWidget>>
  ribi::cmap::QtTestConceptMapWidgetDialog::CreateWidgets() noexcept
{
  const boost::shared_ptr<ConceptMap> m(ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(17));
  assert(m);
  std::vector<boost::shared_ptr<QtConceptMapWidget>> v;
  //Display
  {
    const boost::shared_ptr<QtConceptMap> c(new QtDisplayConceptMap(m));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c));
    v.push_back(w);
  }
  //Edit
  {
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(m));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c));
    v.push_back(w);
  }
  //Rate
  {
    const boost::shared_ptr<QtConceptMap> c(new QtRateConceptMap(m));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c));
    v.push_back(w);
  }
  assert(v.size() == 3 && "There are three display strategies of QtConceptMap");
  return v;
}


void ribi::cmap::QtTestConceptMapWidgetDialog::DoClick(const int button_index)
{
  const QPushButton * const button =  m_buttons[button_index];
  const std::string text = button->text().toStdString();
  const auto command_iter = std::find_if(m_commands.begin(),m_commands.end(),
    [text](boost::shared_ptr<Command> command)
    {
      assert(command);
      return command->ToStr() == text;
    }
  );
  assert(command_iter != m_commands.end());
  assert(*command_iter);
  for (boost::shared_ptr<QtConceptMapWidget> qtwidget: m_qtwidgets)
  {
    assert(qtwidget);
    if (qtwidget->CanDoCommand(*command_iter))
    {
      qtwidget->DoCommand(*command_iter);
    }
  }
}

void ribi::cmap::QtTestConceptMapWidgetDialog::OnClick()
{
  TRACE_FUNC();
  const auto button_iter = std::find_if(m_buttons.begin(),m_buttons.end(),
    [](QPushButton * const button) { return button->hasFocus(); }
  );
  if (button_iter == m_buttons.end()) return;
  const int button_index {
    std::distance(
      m_buttons.begin(),
      button_iter
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
    QtTestConceptMapWidgetDialog d;
    TRACE("Clicking button 0");
    d.DoClick(0);
  }
  {
    QtTestConceptMapWidgetDialog d;
    TRACE("Clicking button 1");
    d.DoClick(1);
  }
  TRACE("Clicking twice");
  {
    QtTestConceptMapWidgetDialog d;
    d.DoClick(0);
    d.DoClick(0);
  }
  {
    QtTestConceptMapWidgetDialog d;
    d.DoClick(0);
    d.DoClick(1);
  }
  {
    QtTestConceptMapWidgetDialog d;
    d.DoClick(1);
    d.DoClick(0);
  }
  {
    QtTestConceptMapWidgetDialog d;
    d.DoClick(1);
    d.DoClick(1);
  }
  TRACE("Random clicking");
  {
    QtTestConceptMapWidgetDialog d;
    assert(d.m_buttons.size() >= 2);
    const int n_buttons = static_cast<int>(d.m_buttons.size());
    for (int i=0; i!=100; ++i)
    {
      d.DoClick( std::rand() % n_buttons);
    }
  }
  TRACE("Finished ribi::cmap::QtTestConceptMapWidgetDialog::Test successfully");
}
#endif
