#include "qtvirtualbastardmenudialog.h"

#include <cassert>
#include <fstream>
#include <thread>
#include <QTimer>
#include "qtvirtualbastardexample1dialog.h"
#include "qtvirtualbastardmaindialog.h"
#include "virtualbastard.h"
#include "ui_qtvirtualbastardmenudialog.h"

QtVirtualBastardMenuDialog::QtVirtualBastardMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtVirtualBastardMenuDialog)
{
  ui->setupUi(this);
}

QtVirtualBastardMenuDialog::~QtVirtualBastardMenuDialog()
{
  delete ui;
}

void QtVirtualBastardMenuDialog::on_button_start_clicked()
{
  QtVirtualBastardMainDialog d;
  d.exec();
}

void QtVirtualBastardMenuDialog::on_button_1_clicked()
{
  //VirtualBastard cannot work, because it needs to create a different script execution thread
  //than from the program
  #ifdef THIS_APPROACH_8758758
  QtVirtualBastardExample1Dialog * const dialog = new QtVirtualBastardExample1Dialog;
  dialog->show();
  //VirtualBastard();
  QApplication::processEvents();
  std::thread t(
    [dialog]
    {
      assert(dialog);
      {
        std::ofstream f("script.sh");
        const QPoint tl = dialog->mapToGlobal(dialog->pos());
        f << "#!/bin/sh" << '\n'
          << "./../../Libraries/libcvautomation/examples/cva-input -s \"mousexy " << tl.x()<< " " << tl.y() << "\"" << '\n'
          << "sleep 1" << '\n';
        f.close();
        std::system("chmod +x script.sh");
        std::system("./script.sh");
      }
      {
        std::ofstream f("script.sh");
        const QPoint tl = dialog->mapToGlobal(dialog->pos());
        f << "#!/bin/sh" << '\n'
          << "./../../Libraries/libcvautomation/examples/cva-input -s \"mousexy "
            << tl.x() << " " << tl.y() << "\"" << '\n'
          << "sleep 1" << '\n'
          << "./../../Libraries/libcvautomation/examples/cva-input -s \"mousexy "
            << (tl.x() + dialog->width()) << " " << tl.y() << "\"" << '\n'
          << "sleep 1" << '\n'
          << "./../../Libraries/libcvautomation/examples/cva-input -s \"mousexy "
            << (tl.x() + dialog->width()) << " " << tl.y() + (dialog->height()) << "\"" << '\n'
          << "sleep 1" << '\n'
          << "./../../Libraries/libcvautomation/examples/cva-input -s \"mousexy "
            << tl.x() << " " << tl.y() + (dialog->height()) << "\"" << '\n'
          ;
        f.close();
        std::system("chmod +x script.sh");
        std::system("./script.sh");
      }
    }
  );
  t.join();
  dialog->close();
  delete dialog;
  #endif

  #ifdef THIS_APPROACH_872534872
  {
    QtVirtualBastardExample1Dialog * const dialog = new QtVirtualBastardExample1Dialog;

    VirtualBastard();

    std::thread t(
      [dialog]
      {
        assert(dialog);
        //Point to the four corners of the dialog
        //Do the top-left point twice, because sometimes the first misses
        const int sleeptime = 500; //msecs
        VirtualBastard::Sleep(sleeptime);
        VirtualBastard();
        {
          const QPoint tl = dialog->mapToGlobal(dialog->pos());
          VirtualBastard::SetMousePos(tl.x(),tl.y());
          VirtualBastard::Sleep(sleeptime);
        }
        {
          const QPoint tl = dialog->mapToGlobal(dialog->pos());
          VirtualBastard::SetMousePos(tl.x(),tl.y());
          VirtualBastard::Sleep(sleeptime);
        }
        {
          const QPoint tl = dialog->mapToGlobal(dialog->pos());
          VirtualBastard::SetMousePos(tl.x() + dialog->width(),tl.y());
          VirtualBastard::Sleep(sleeptime);
        }
        {
          const QPoint tl = dialog->mapToGlobal(dialog->pos());
          VirtualBastard::SetMousePos(tl.x() + dialog->width(),tl.y() + dialog->height());
          VirtualBastard::Sleep(sleeptime);
        }
        {
          const QPoint tl = dialog->mapToGlobal(dialog->pos());
          VirtualBastard::SetMousePos(tl.x(),tl.y() + dialog->height());
          VirtualBastard::Sleep(sleeptime);
        }
        //Click the checkboxes
        dialog->close();
        delete dialog;
      }
    );

    t.detach();
    dialog->show();

  }
  #endif
  //this->show();

}



