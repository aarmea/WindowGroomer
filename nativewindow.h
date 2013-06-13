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

#define CSTRING_LEN 256

// Windows-specific includes
#ifdef Q_WS_WIN
#include <Windows.h>
#pragma comment(lib, "User32.lib")
typedef HWND WindowId;
#endif

// Mac-specific includes
#ifdef Q_WS_MAC
#endif

// Linux/Unix-specific includes
#ifdef Q_WS_X11
#include <QX11Info>
#include <X11/Xlib.h>
struct WindowId {
  Window handle;
  Display *display;
};
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
