VERSION = 0.1.1
QMAKE_TARGET_COMPANY = "Albert Armea"
QMAKE_TARGET_PRODUCT = "WindowGroomer"
QMAKE_TARGET_DESCRIPTION = "Position application windows on a grid."
QMAKE_TARGET_COPYRIGHT = "2012-2013"

# Qt does not include the directory the project file is in by default
INCLUDEPATH += .

CONFIG += \
  qxt

QXT += \
  core \
  gui

HEADERS = \
  "gui/gridwindow.h" \
  "gui/gridwidget.h" \
  "gui/settingswindow.h" \
  "wm/nativewindow.h"

SOURCES = \
  "main.cpp" \
  "gui/gridwindow.cpp" \
  "gui/gridwidget.cpp" \
  "gui/settingswindow.cpp"

win32:SOURCES += "wm/nativewindow-win.cpp"
unix:!mac:SOURCES += "wm/nativewindow-x11.cpp"

RESOURCES = windowgroomer.qrc

win32:RC_FILE = windowgroomer.rc

DEFINES += \
  APP_VERSION=\"\\\"$$VERSION\\\"\" \
  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
