#include "conceptmapwidget.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmap.h"
#include "conceptmapfactory.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandfactory.h"
#include "conceptmapwidgetfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::Widget::Widget(const boost::shared_ptr<ConceptMap> conceptmap)
  : m_signal_concept_map_changed{}, //Signals first, as these are public
    m_conceptmap(conceptmap),
    m_focus{nullptr},
    m_undo{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert( (m_conceptmap || !m_conceptmap )
    && "Allow a widget with and without an actual concept map");
}

#ifndef NDEBUG
ribi::cmap::Widget::Widget(const Widget& other)
  : m_signal_concept_map_changed{}, //Signals first, as these are public
    m_conceptmap(ConceptMapFactory::DeepCopy(other.m_conceptmap)),
    m_focus{nullptr},
    m_undo{}
{
  assert(static_cast<bool>(m_conceptmap) == static_cast<bool>(other.m_conceptmap));
  assert( (!m_conceptmap || *m_conceptmap == *other.m_conceptmap) && "Must be a copy");
  assert( (!m_conceptmap || m_conceptmap != other.m_conceptmap) && "Must be a deep copy");
  assert( (m_focus == other.m_focus || m_focus != other.m_focus)
    && "Cannot copy focus");

  assert( (m_undo == other.m_undo || m_undo != other.m_undo)
    && "Cannot copy undo");
}
#endif

bool ribi::cmap::Widget::CanDoCommand(const boost::shared_ptr<Command> command) const noexcept
{
  return command->CanDoCommand(this);
}

void ribi::cmap::Widget::DoCommand(const boost::shared_ptr<Command> command) noexcept
{
  assert(CanDoCommand(command));

  //Undo
  m_undo.push_back(command);

  //Actually do the move
  command->DoCommand(this);
}

const std::string ribi::cmap::Widget::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::cmap::Widget::GetVersionHistory() noexcept
{
  return {
    "2013-12-xx: Version 1.0: initial version",
    "2013-12-23: Version 1.1: started versioning"
  };
}

void ribi::cmap::Widget::SetConceptMap(const boost::shared_ptr<ConceptMap> conceptmap) noexcept
{
  m_conceptmap = conceptmap;
  m_signal_concept_map_changed();
}

#ifndef NDEBUG
void ribi::cmap::Widget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::Widget::Test()");
  //Test if individual commands have the intended effect
  //Delete concept map
  {
    static int cnt_no = 0;
    static int cnt_yes = 0;
    for (const boost::shared_ptr<Widget> widget:
      WidgetFactory::GetAllTests())
    {
      CommandDeleteConceptMap c;
      if (widget->GetConceptMap())
      {
        assert(c.CanDoCommand(widget.get()) && "Can delete a concept map when present");
        c.DoCommand(widget.get());
        assert(!widget->GetConceptMap() && "Concept map must be deleted");
        c.Undo();
        assert(widget->GetConceptMap() && "Concept map must be restored by undo");
        ++cnt_yes;
      }
      else
      {
        assert(!widget->GetConceptMap());
        assert(!c.CanDoCommand(widget.get()) && "Cannot delete a concept map when absent");
        ++cnt_no;
      }
    }
    assert(cnt_no > 0);
    assert(cnt_yes > 0);
  }
  //Start concept map
  {
    static int cnt_no = 0;
    static int cnt_yes = 0;

    for (const boost::shared_ptr<Widget> widget:
      WidgetFactory::GetAllTests())
    {
      CommandStartConceptMap c;
      if (!widget->GetConceptMap())
      {
        assert(c.CanDoCommand(widget.get()) && "Can start a concept map when none is present");
        c.DoCommand(widget.get());
        assert(widget->GetConceptMap() && "Concept map must be created");
        c.Undo();
        assert(!widget->GetConceptMap() && "Concept map must be deleted by undo");
        ++cnt_yes;
      }
      else
      {
        assert(widget->GetConceptMap());
        assert(!c.CanDoCommand(widget.get()) && "Cannot start when a concept map already exists");
        ++cnt_no;
      }
    }
    assert(cnt_no > 0);
    assert(cnt_yes > 0);
  }
  //Test all commands do and undo
  for (const boost::shared_ptr<Widget> widget:
    WidgetFactory::GetAllTests())
  {
    assert(widget);

    for (const boost::shared_ptr<Command> command: CommandFactory::CreateTestCommands())
    {
      assert(command);
      if (widget->CanDoCommand(command))
      {
        const ribi::cmap::Widget prev_widget(*widget);
        assert(prev_widget == *widget);
        widget->DoCommand(command);
        assert(prev_widget != *widget);
        widget->Undo();
        assert(prev_widget == *widget);
      }
    }
  }
  TRACE("Finished ribi::cmap::Widget::Test()");
}
#endif

void ribi::cmap::Widget::Undo()
{
  assert(!m_undo.empty());
  assert(m_undo.back());
  m_undo.back()->Undo();
  m_undo.pop_back();
}

bool ribi::cmap::operator==(const Widget& lhs, const Widget& rhs)
{
  if (static_cast<bool>(lhs.m_conceptmap.get()) != static_cast<bool>(rhs.m_conceptmap.get()))
  {
    return false;
  }
  assert(static_cast<bool>(nullptr) == static_cast<bool>(nullptr));
  if (lhs.m_conceptmap && *lhs.m_conceptmap != *rhs.m_conceptmap) return false;
  if (lhs.m_focus != rhs.m_focus) return false;
  if (lhs.m_undo.size() != rhs.m_undo.size()) return false;
  return std::equal(
    std::begin(lhs.m_undo),
    std::end(lhs.m_undo),
    std::begin(rhs.m_undo),
    [](boost::shared_ptr<const Command> p,
       boost::shared_ptr<const Command> q)
    {
      return p->ToStr() == q->ToStr();
    }
  );
}

bool ribi::cmap::operator!=(const Widget& lhs, const Widget& rhs)
{
  return !(lhs == rhs);
}
