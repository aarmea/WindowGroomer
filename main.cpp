#include <QApplication>

#include "gridwindow.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(windowgroomer);

  QApplication app(argc, argv);
  QApplication::setQuitOnLastWindowClosed(false);
  GridWindow window;

  // Don't window.show(); so there is no splash screen

  return app.exec();
}
