#ifndef QTCONCEPTMAPCONCEPTMAPWIDGET_H
#define QTCONCEPTMAPCONCEPTMAPWIDGET_H

#include "qtconceptmapfwd.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

#include <boost/shared_ptr.hpp>
#include <QWidget>

#include "qtkeyboardfriendlygraphicsview.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///QtConceptMapWidget implements a higher-level interface of
///QtConceptMap, driven by Commands
///
///Sure, you can click it and interact with it by mouse and keyboard:
///these interactions will be converted to commands, so behind the scenes
///the concept map is not interacted with directly
struct QtConceptMapWidget : public ribi::QtKeyboardFriendlyGraphicsView
{
  QtConceptMapWidget(const boost::shared_ptr<QtConceptMap> qtconceptmap);
  ~QtConceptMapWidget() noexcept {}

  bool CanDoCommand(const boost::shared_ptr<const Command> command) const noexcept;
  void DoCommand(const boost::shared_ptr<Command> command) noexcept;

  ///QtConceptMapWidget intercepts all user interactions and converts these
  ///to commands for Widget
  void keyPressEvent(QKeyEvent *) noexcept;
  void mouseDoubleClickEvent(QMouseEvent *) noexcept;
  void mouseMoveEvent(QMouseEvent *) noexcept;
  void mousePressEvent(QMouseEvent *) noexcept;
  //void showEvent(QShowEvent *event) noexcept;

  private:
  ///Displaying the concept map, the View
  ///This display is connected to the Widget/Model by signals
  ///and listening, instead of acted upon
  boost::shared_ptr<QtConceptMap> m_qtconceptmap;

  ///The nonvisual concept map widget, the Model
  ///The Widget is worked upon, the signal it emits are listened to by the QtConceptMap/View
  boost::shared_ptr<Widget> m_widget;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Called when Widget emits m_signal_add_node
  ///Which is emitted when the ConceptMap has a node added
  void OnAddNode(const boost::shared_ptr<Node> node) noexcept;

  ///Called when Widget emits m_signal_concept_map_changed
  ///Which is emitted when the ConceptMap changes as a whole
  void OnConceptMapChanged() noexcept;

  ///Called when Widget emits m_signal_add_node
  ///Which is emitted when the ConceptMap has a node added
  void OnDeleteNode(const boost::shared_ptr<Node> node) noexcept;

  ///Called when Widget emits m_signal_lose_focus_node
  ///Which is emitted when a Node loses focus
  ///A Node has no idea of losing focus
  void OnLoseFocusNode(const boost::shared_ptr<Node> node) noexcept;

  ///Called when Widget emits m_signal_set_focus_node
  ///Which is emitted when a Node is given focus
  ///A Node has no idea of having focus
  void OnSetFocusNode(const boost::shared_ptr<Node> node) noexcept;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPCONCEPTMAPWIDGET_H
