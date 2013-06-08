VERSION = 0.1.0
QMAKE_TARGET_COMPANY = "Albert Armea"
QMAKE_TARGET_PRODUCT = "WindowGroomer"
QMAKE_TARGET_DESCRIPTION = "Position application windows on a grid."
QMAKE_TARGET_COPYRIGHT = "2012-2013"

CONFIG += \
  qxt

QXT += \
  core \
  gui

HEADERS = \
  gridwindow.h \
  gridwidget.h \
  nativewindow.h

SOURCES = \
  main.cpp \
  gridwindow.cpp \
  gridwidget.cpp

win32:SOURCES += nativewindow-win.cpp

RESOURCES = windowgroomer.qrc

win32:RC_FILE = windowgroomer.rc

DEFINES += \
  APP_VERSION=\"\\\"$$VERSION\\\"\" \
  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
