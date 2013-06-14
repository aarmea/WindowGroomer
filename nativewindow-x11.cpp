#include "nativewindow.h"

// Hard-coded sizes of window decorations because there is no window manager-
// agnostic way of getting them with X11
// TOOD: add this to the preferences
int NativeWindow::titleBarHeight = 27;
int NativeWindow::sideBorderWidth = 1;
int NativeWindow::bottomBorderHeight = 1;

NativeWindow::NativeWindow()
{
  // Default constructor uses the current foreground window
  getFront();
}

void NativeWindow::getFront()
{
  // Get the currently focused window
  // Method based on the X11 version of QxtWindowSystem::activeWindow()
  // We can't just use XGetInputFocus because WindowGroomer has keyboard focus
  // after the shortcut is pressed
  Atom type = 0;
  int format = 0;
  uchar *data = NULL; // X11 will not directly write to data of type Window*
  window.display = QX11Info::display();
  Window root = QX11Info::appRootWindow();
  ulong count, after;
  if (
    XGetWindowProperty(window.display, root,
      XInternAtom(window.display, "_NET_ACTIVE_WINDOW", True),
      0, 1024 * sizeof(Window) / 4, False, AnyPropertyType,
      &type, &format, &count, &after, &data) == Success && (data != NULL)
  ) {
    Window *allWindows = reinterpret_cast<Window *>(data);
    window.handle = allWindows[0];
    XFree(allWindows);
  }
}

QString NativeWindow::title()
{
  // TODO: title is sometimes blank
  char *buffer;
  XFetchName(window.display, window.handle, &buffer);
  QString title = QString::fromUtf8(buffer);
  XFree(buffer);
  return title;
}

bool NativeWindow::resize(QRect size)
{
  // X11 positions its windows excluding decorations (title bar and borders),
  // so we need to account for that manually
  int xPos = size.x() + sideBorderWidth;
  int yPos = size.y();
  int width = size.width() - 2*sideBorderWidth;
  int height = size.height() - titleBarHeight - bottomBorderHeight;
  // XMoveResizeWindow returns 0 on success and nonzero on failure
  return XMoveResizeWindow(window.display, window.handle,
    xPos, yPos, width, height);
}
