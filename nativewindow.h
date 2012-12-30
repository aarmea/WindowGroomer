/* NativeWindow.h

A cross-platform way to represent and modify native windows.
We can't use QxtWindowSystem because we need Mac support and window resizing.
*/

#ifndef NATIVEWINDOW_H
#define NATIVEWINDOW_H

// For OS-specific macros
#include <qglobal.h>

#include <QString>
#include <QRect>

#ifdef Q_WS_WIN
// Windows-specific includes
#include <Windows.h>
#pragma comment(lib, "User32.lib")
typedef HWND WindowId;
#endif

#ifdef Q_WS_MAC
// Mac-specific includes
#endif

#ifdef Q_WS_X11
// Linux/Unix-specific includes
#endif

class NativeWindow {
public:
  NativeWindow();
  void getFront();

  QString title();

  bool resize(QRect size);

private:
  WindowId window;
};

#endif
