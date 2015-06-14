#ifndef QTTANKBATTALIONGAMEDIALOG
#define QTTANKBATTALIONGAMEDIALOG

/*

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTankBattalionGameDialog;
}

namespace ribi {
namespace taba {

struct QtArenaWidget;


class QtTankBattalionGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTankBattalionGameDialog(QWidget *parent = 0);
  QtTankBattalionGameDialog(const QtTankBattalionGameDialog&) = delete;
  QtTankBattalionGameDialog& operator=(const QtTankBattalionGameDialog&) = delete;
  ~QtTankBattalionGameDialog();

private:
  boost::shared_ptr<QtArenaWidget> m_game;
  Ui::QtTankBattalionGameDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);
  void paintEvent(QPaintEvent *);
  //void resizeEvent(QResizeEvent *);
};

} //~namespace taba
} //~namespace ribi

*/

#endif // QTTANKBATTALIONGAMEDIALOG
