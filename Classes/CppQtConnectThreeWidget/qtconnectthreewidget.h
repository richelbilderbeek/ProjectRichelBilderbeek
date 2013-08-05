#ifndef QTCONNECTTHREEWIDGET_H
#define QTCONNECTTHREEWIDGET_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <bitset>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

#include <QWidget>

#include "connectthreewidget.h" //thanks to MOC :-(
#include "connectthree.h"       //thanks to MOC :-(
//struct ConnectThreeWidget;
struct ConnectThreeResources;

class QtConnectThreeWidget : public QWidget
{
    Q_OBJECT
public:
  explicit QtConnectThreeWidget(
    const ConnectThreeResources& resources,
    QWidget *parent = 0,
    const std::bitset<3>& is_player_human = std::bitset<3>(true),
    const int n_cols = 16,
    const int n_rows = 12);

  void DoComputerTurn();
  int GetActivePlayer() const;
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
  int GetWinner() const;
  bool IsComputerTurn() const;

  ///m_signal_valid_move is emitted on a valid move,
  ///causing the game to be terminated or let
  ///the next player do his/her move.
  boost::signals2::signal<void ()> m_signal_valid_move;

signals:

public slots:

protected:
  void mousePressEvent(QMouseEvent * e);
  void paintEvent(QPaintEvent *);


  private:

  boost::scoped_ptr<ConnectThreeWidget> m_widget;
  const QImage m_player1;
  const QImage m_player2;
  const QImage m_player3;
  const QImage m_empty;
  const QImage& GetImage(const int sprite) const;

  static const int m_sprite_width;
  static const int m_sprite_height;

};

#endif // QTCONNECTTHREEWIDGET_H
