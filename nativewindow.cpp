#include "nativewindow.h"

// Platform-agnostic implementations
NativeWindow::NativeWindow()
{
  // Default constructor uses the current foreground window
  getFront();
}

#ifdef Q_WS_WIN
// Windows-specific implementations
void NativeWindow::getFront()
{
  window = GetForegroundWindow();
}

QString NativeWindow::title()
{
  // Windows-style string
  LPTSTR buffer = new wchar_t[256];
  GetWindowText(window, buffer, 256);
  QString title = QString::fromUtf16(buffer);
  delete[] buffer;
  return title;
}

bool NativeWindow::resize(QRect size)
{
  return SetWindowPos(window, 0,
    size.x(), size.y(), size.width(), size.height(),
    SWP_ASYNCWINDOWPOS | SWP_NOZORDER);
}
#endif

#ifdef Q_WS_MAC
// Mac-specific implementations
#endif

#ifdef Q_WS_X11
// Linux/Unix-specific implementations
#endif
