#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include <QDialog>

struct QGraphicsScene;
struct QGraphicsPixmapItem;
struct QImage;
struct QPixmap;
struct QTimer;
struct Player;

namespace Ui {
  class DialogGame;
}

const std::vector<boost::shared_ptr<Player> > CreatePlayers();

class DialogGame : public QDialog
{
  Q_OBJECT

public:
  explicit DialogGame(QWidget *parent = 0,
    const std::vector<boost::shared_ptr<Player> >& players = CreatePlayers());
  ~DialogGame();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogGame *ui;
  QTimer * m_timer;
  QPixmap * m_pixmap;
  const int m_width;
  const int m_height;
  std::vector<boost::shared_ptr<Player> > m_players;

  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent*);
};

#endif // DIALOGGAME_H
