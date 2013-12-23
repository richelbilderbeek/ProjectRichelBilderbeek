#include "conceptmapwidget.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandfactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::Widget::Widget(const boost::shared_ptr<ConceptMap> conceptmap)
  : m_conceptmap(conceptmap),
    m_focus{nullptr},
    m_undo{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert( (m_conceptmap || !m_conceptmap )
    && "Allow a widget with and without an actual concept map");
}

ribi::cmap::Widget::Widget(const Widget& other)
  : m_conceptmap(ConceptMapFactory::DeepCopy(other.m_conceptmap)),
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

bool ribi::cmap::Widget::CanDoCommand(const boost::shared_ptr<Command> command) const noexcept
{
  return command->CanDoCommand(this);
}

void ribi::cmap::Widget::DoCommand(const boost::shared_ptr<Command> command) noexcept
{
  assert(CanDoCommand(command));

  //Undo
  {
    const boost::shared_ptr<Widget> prev_widget {
      new Widget(*this)
    };
    m_undo.push_back(std::make_pair(prev_widget,command));
  }

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

#ifndef NDEBUG
void ribi::cmap::Widget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::Widget::Test()");
  for (const boost::shared_ptr<ribi::cmap::ConceptMap> map:
    ribi::cmap::ConceptMapFactory::GetAllTests())
  {
    TRACE_FUNC();
    assert(map || !map);
    ribi::cmap::Widget widget(map);
    assert(widget == widget);

    for (const boost::shared_ptr<Command> command: CommandFactory::CreateTestCommands())
    {
      assert(command);
      TRACE(command->ToStr());
      if (widget.CanDoCommand(command))
      {
        TRACE(command->ToStr());
        const ribi::cmap::Widget prev_widget(widget);
        TRACE(command->ToStr());
        assert(prev_widget == widget);
        TRACE(command->ToStr());
        widget.DoCommand(command);
        TRACE(command->ToStr());
        assert(prev_widget != widget);
        TRACE(command->ToStr());
        widget.Undo();
        TRACE(command->ToStr());
        assert(prev_widget == widget);
        TRACE(command->ToStr());
      }
    }
  }
  TRACE("Finished ribi::cmap::Widget::Test()");
}
#endif

void ribi::cmap::Widget::Undo()
{
  assert(!m_undo.empty());
  this->m_conceptmap = (*m_undo.back().first).GetConceptMap();
  assert(!m_conceptmap || *m_conceptmap == *(*m_undo.back().first).GetConceptMap());
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
    [](const std::pair<boost::shared_ptr<Widget>,boost::shared_ptr<const Command>> p,
       const std::pair<boost::shared_ptr<Widget>,boost::shared_ptr<const Command>> q)
    {
      return *p.first == *q.first
        && p.second->ToStr() == q.second->ToStr();
    }
  );
}

bool ribi::cmap::operator!=(const Widget& lhs, const Widget& rhs)
{
  return !(lhs == rhs);
}
