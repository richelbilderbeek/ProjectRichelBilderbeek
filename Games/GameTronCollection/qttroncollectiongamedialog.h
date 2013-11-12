#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <vector>

#include <boost/shared_ptr.hpp>

#include <QDialog>

#include "player.h"
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QGraphicsPixmapItem;
struct QImage;
struct QPixmap;
struct QTimer;

namespace Ui { class QtTronCollectionGameDialog; }

namespace ribi {

struct Player;

class QtTronCollectionGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTronCollectionGameDialog(QWidget *parent = 0,
    const std::vector<boost::shared_ptr<Player> > players = CreatePlayers());
  QtTronCollectionGameDialog(const QtTronCollectionGameDialog&) = delete;
  QtTronCollectionGameDialog& operator=(const QtTronCollectionGameDialog&) = delete;
  ~QtTronCollectionGameDialog();

private:
  Ui::QtTronCollectionGameDialog *ui;
  QTimer * m_timer;
  QPixmap * m_pixmap;
  const int m_width;
  const int m_height;
  std::vector<boost::shared_ptr<Player> > m_players;

  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent*);

  static const std::vector<boost::shared_ptr<Player> > CreatePlayers();
};

} //~namespace ribi

#endif // DIALOGGAME_H
