#include <QApplication>

#include "gridwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  GridWindow window;

  // Don't window.show(); so there is no splash screen

  return app.exec();
}
