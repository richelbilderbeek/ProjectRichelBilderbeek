#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include <QGLWidget>
#pragma GCC diagnostic pop

struct MyWidget : public QGLWidget
{
  //Q_OBJECT

public:
  MyWidget(QWidget * const parent = nullptr) : QGLWidget(parent) {}

protected:
  void initializeGL()
  {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
  }
  void resizeGL(int width, int height )
  {
    glViewport(0, 0,width,height);
    glFrustum(-1.0,1.0,-1.0,1.0,-1.0,1.0);
  }
  void paintGL()
  {
    //glRotatef(...);
    //glMaterialfv(...);
    glBegin(GL_TRIANGLES);
      glVertex3f( 1.0, 0.0, 0.0);
      glVertex3f( 0.0, 1.0, 0.0);
      glVertex3f( 0.0, 0.0, 1.0);
    glEnd();
  }
};

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MyWidget * const widget = new MyWidget;
  widget->show();
  return a.exec();
}
