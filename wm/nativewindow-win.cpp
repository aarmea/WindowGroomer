#include "wm/nativewindow.h"

NativeWindow::NativeWindow()
{
  // Default constructor uses the current foreground window
  getFront();
}

void NativeWindow::getFront()
{
  window = GetForegroundWindow();
}

QString NativeWindow::title()
{
  // Windows-style string
  LPTSTR buffer = new TCHAR[CSTRING_LEN];
  GetWindowText(window, buffer, CSTRING_LEN);
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
