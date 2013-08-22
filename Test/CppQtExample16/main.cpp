#include <cassert>
#include <boost/shared_ptr.hpp>
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Load the resource in a pixmap
  const QPixmap pixmap(":/MyImages/BeerSmall.bmp");
  assert(!pixmap.isNull() && "Assume bitmap is found");

  //Put the pixmap in a label
  boost::shared_ptr<QLabel> label(new QLabel);
  label->setPixmap(pixmap);

  //Add label in a layout
  boost::shared_ptr<QVBoxLayout> layout(new QVBoxLayout);
  layout->addWidget( label.get() );

  //Create and show a window
  boost::shared_ptr<QDialog> dialog(new QDialog);
  dialog->setLayout(layout.get());
  dialog->show();

  return a.exec();
}
