#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <vector>

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "tronplayer.h"
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QGraphicsPixmapItem;
struct QImage;
struct QPixmap;
struct QTimer;

namespace Ui { class QtTronGameDialog; }

namespace ribi {
namespace tron {

struct Player;

class QtTronGameDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTronGameDialog(QWidget *parent = 0,
    const std::vector<boost::shared_ptr<Player> > players = CreatePlayers());
  QtTronGameDialog(const QtTronGameDialog&) = delete;
  QtTronGameDialog& operator=(const QtTronGameDialog&) = delete;
  ~QtTronGameDialog() noexcept;

private:
  Ui::QtTronGameDialog *ui;

  QImage * m_image;
  std::vector<boost::shared_ptr<Player> > m_players;
  QTimer * m_timer;

  void OnTimer();
  void resizeEvent(QResizeEvent*);

  static const std::vector<boost::shared_ptr<Player> > CreatePlayers();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tron
} //~namespace ribi

#endif // DIALOGGAME_H
